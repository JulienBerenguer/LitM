// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleManager.h"
#include "Sheet.h"
#include "PuzzleWidget.h"
#include "Engine/World.h"

APuzzleManager::APuzzleManager() {

}

// Called when the game starts or when spawned
void APuzzleManager::BeginPlay()
{
	Super::BeginPlay();

	// Initialisation
	Init();

}

void APuzzleManager::Init() {

	// Set la référence du Puzzle dans les pièces pour faire un lien enfant -> parent
	for (int32 Index = 0; Index != PuzzlePiecesList.Num(); ++Index)
	{
		// Pièce valide
		if (IsValid(PuzzlePiecesList[Index])) {
			// Ajoute la référence
			PuzzlePiecesList[Index]->InitPuzzle(this);
		}
	}

	// Init la liste des pièces trouvées
	PuzzlePiecesFoundList.Init(false, PuzzlePiecesList.Num());

	//Sheet = CreateWidget<USheetWidget>(GetWorld(), WidgetClass);

	// The WidgetClass exist ?
	if (IsValid(WidgetClass)) {
		// Create SheetWidget
		PuzzleWidget = CreateWidget<UPuzzleWidget>(GetWorld(), WidgetClass);

		// Init the text, style & background texture of SheetWidget
		if (IsValid(PuzzleWidget)) {
			UE_LOG(LogTemp, Warning, TEXT("PuzzleManager.cpp : Widget OK"));

			// Widget created => show it at start ?
			if (ShowPuzzleWidgetAtStart) {
				ShowHidePuzzle();
			}
		}
		// Error at widget creation
		else {
			UE_LOG(LogTemp, Warning, TEXT("PuzzleManager.cpp : Widget NOT OK"));
		}
	}
}


void APuzzleManager::ShowHidePuzzle() {
	// Affiche le puzzle
	if (!IsPuzzleWidgetOpened) ShowPuzzle();
	// Cache le puzzle
	else HidePuzzle();
	// Changement du flag
	IsPuzzleWidgetOpened = !IsPuzzleWidgetOpened;
}
void APuzzleManager::ShowPuzzle() {
	PuzzleWidget->AddToViewport();
	PuzzleUpdate();	// Réaffiche les pièces déjà découvertes (remises en invisibles par le HidePuzzle())
}

void APuzzleManager::HidePuzzle() {
	PuzzleWidget->RemoveFromViewport();
}


// Mise à jour des pièces de puzzle sur le widget
void APuzzleManager::PuzzleUpdate() {
	// Boucle pour ajouter la pièce si elle est valide
	for (int32 Index = 0; Index != PuzzlePiecesList.Num(); ++Index)
	{
		// Pièce valide
		if (IsValid(PuzzlePiecesList[Index])) {
			// Mise à jour de la liste des pièces trouvées
			if (PuzzlePiecesFoundList[Index] == true) {
				// Appel de la fonction pour afficher la pièce sur le widget du puzzle
				PuzzleWidget->DisplayPuzzlePiece(Index);
			}
		}
	}
}

bool APuzzleManager::FoundPuzzlePiece(class ASheet* NewPuzzlePiece) {
	// Pièce trouvée valide
	if (IsValid(NewPuzzlePiece)) {
		// Boucle pour ajouter la pièce si elle est valide
		for (int32 Index = 0; Index != PuzzlePiecesList.Num(); ++Index)
		{
			// Pièce valide
			if (IsValid(PuzzlePiecesList[Index])) {
				// Pièce dans la liste
				if (NewPuzzlePiece == PuzzlePiecesList[Index]) {
					// Mise à jour de la liste des pièces trouvées
					PuzzlePiecesFoundList[Index] = true;
					// Appel de la fonction pour afficher la pièce sur le widget du puzzle
					PuzzleWidget->DisplayPuzzlePiece(Index);
					
					// Une pièce a été trouvée => appelle l'event OnPuzzlePieceFound et lui passe le nombre de pièces (PuzzlePiecesCount)
					OnPuzzlePieceFound(PuzzlePiecesFoundCount());

					// Est-ce que le puzzle a été complété ? Si oui alors on appelle l'event OnPuzzleComplete()
					if (PuzzleIsCompleted()) OnPuzzleComplete();
				}
			}
		}
	}
	// Pièce trouvée non valide
	else return false;

	return true;
}


int APuzzleManager::PuzzlePiecesFoundCount() {
	int NbPuzzlePiecesFound = 0;

	// Liste toutes les pièces trouvées
	for (bool PuzzlePiece : PuzzlePiecesFoundList)
	{
		// Si une pièce a déjà été découverte
		if (PuzzlePiece == true) NbPuzzlePiecesFound++;
	}

	// Retourne le nombre de pièces trouvées
	return NbPuzzlePiecesFound;
}

int APuzzleManager::PuzzlePiecesTotalCount() {
	int NbPuzzlePieces = 0;

	// Liste toutes les pièces enregistrées
	for (ASheet* PuzzlePiece : PuzzlePiecesList)
	{
		// Si une pièce enregistrée est valide
		if (IsValid(PuzzlePiece)) NbPuzzlePieces++;
	}

	// Retourne le nombre de pièces enregistrées
	return NbPuzzlePieces;
}


bool APuzzleManager::PuzzleIsCompleted() {

	// Liste toutes les pièces trouvées
	for (bool PuzzlePiece : PuzzlePiecesFoundList)
	{
		// Si une pièce est manquante => renvoie false
		if (PuzzlePiece == false) return false;
	}
	// Aucune pièce n'est manquante => le puzzle est complet => renvoie true
	return true;
}