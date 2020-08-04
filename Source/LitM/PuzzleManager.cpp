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

	// Set la r�f�rence du Puzzle dans les pi�ces pour faire un lien enfant -> parent
	for (int32 Index = 0; Index != PuzzlePiecesList.Num(); ++Index)
	{
		// Pi�ce valide
		if (IsValid(PuzzlePiecesList[Index])) {
			// Ajoute la r�f�rence
			PuzzlePiecesList[Index]->InitPuzzle(this);
		}
	}

	// Init la liste des pi�ces trouv�es
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
	PuzzleUpdate();	// R�affiche les pi�ces d�j� d�couvertes (remises en invisibles par le HidePuzzle())
}

void APuzzleManager::HidePuzzle() {
	PuzzleWidget->RemoveFromViewport();
}


// Mise � jour des pi�ces de puzzle sur le widget
void APuzzleManager::PuzzleUpdate() {
	// Boucle pour ajouter la pi�ce si elle est valide
	for (int32 Index = 0; Index != PuzzlePiecesList.Num(); ++Index)
	{
		// Pi�ce valide
		if (IsValid(PuzzlePiecesList[Index])) {
			// Mise � jour de la liste des pi�ces trouv�es
			if (PuzzlePiecesFoundList[Index] == true) {
				// Appel de la fonction pour afficher la pi�ce sur le widget du puzzle
				PuzzleWidget->DisplayPuzzlePiece(Index);
			}
		}
	}
}

bool APuzzleManager::FoundPuzzlePiece(class ASheet* NewPuzzlePiece) {
	// Pi�ce trouv�e valide
	if (IsValid(NewPuzzlePiece)) {
		// Boucle pour ajouter la pi�ce si elle est valide
		for (int32 Index = 0; Index != PuzzlePiecesList.Num(); ++Index)
		{
			// Pi�ce valide
			if (IsValid(PuzzlePiecesList[Index])) {
				// Pi�ce dans la liste
				if (NewPuzzlePiece == PuzzlePiecesList[Index]) {
					// Mise � jour de la liste des pi�ces trouv�es
					PuzzlePiecesFoundList[Index] = true;
					// Appel de la fonction pour afficher la pi�ce sur le widget du puzzle
					PuzzleWidget->DisplayPuzzlePiece(Index);
					
					// Une pi�ce a �t� trouv�e => appelle l'event OnPuzzlePieceFound et lui passe le nombre de pi�ces (PuzzlePiecesCount)
					OnPuzzlePieceFound(PuzzlePiecesFoundCount());

					// Est-ce que le puzzle a �t� compl�t� ? Si oui alors on appelle l'event OnPuzzleComplete()
					if (PuzzleIsCompleted()) OnPuzzleComplete();
				}
			}
		}
	}
	// Pi�ce trouv�e non valide
	else return false;

	return true;
}


int APuzzleManager::PuzzlePiecesFoundCount() {
	int NbPuzzlePiecesFound = 0;

	// Liste toutes les pi�ces trouv�es
	for (bool PuzzlePiece : PuzzlePiecesFoundList)
	{
		// Si une pi�ce a d�j� �t� d�couverte
		if (PuzzlePiece == true) NbPuzzlePiecesFound++;
	}

	// Retourne le nombre de pi�ces trouv�es
	return NbPuzzlePiecesFound;
}

int APuzzleManager::PuzzlePiecesTotalCount() {
	int NbPuzzlePieces = 0;

	// Liste toutes les pi�ces enregistr�es
	for (ASheet* PuzzlePiece : PuzzlePiecesList)
	{
		// Si une pi�ce enregistr�e est valide
		if (IsValid(PuzzlePiece)) NbPuzzlePieces++;
	}

	// Retourne le nombre de pi�ces enregistr�es
	return NbPuzzlePieces;
}


bool APuzzleManager::PuzzleIsCompleted() {

	// Liste toutes les pi�ces trouv�es
	for (bool PuzzlePiece : PuzzlePiecesFoundList)
	{
		// Si une pi�ce est manquante => renvoie false
		if (PuzzlePiece == false) return false;
	}
	// Aucune pi�ce n'est manquante => le puzzle est complet => renvoie true
	return true;
}