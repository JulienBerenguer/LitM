// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "UObject/NoExportTypes.h"
#include "PuzzleWidget.h"
#include "GameFramework/Actor.h"
#include "PuzzleManager.generated.h"

/**
 * Guide d'utilisation : 
 * 1/ Instancier ce PuzzleManager dans le niveau
 * 2/ Instancier des BP_Sheet
 * 3/ Lier ces derniers dans le tableau de pièces de puzzle dans l'ordre voulu
 * 4/ Lier les images du Widget qu'utilise le PuzzleManager dans -le même ordre- que précédemment (dévoile la pièce par index)
 * 5/ Réglage des paramètres du PuzzleManager, des pièces et des Widget du PuzzleManager et des pièces
 */
UCLASS(BlueprintType, Blueprintable)
class LITM_API APuzzleManager : public AActor
{
	GENERATED_BODY()

public:
	APuzzleManager();

	// VARIABLES
public:
	// Widget à utiliser
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Manager - Puzzle")
		TSubclassOf<class UPuzzleWidget> WidgetClass;
	// Liste des pièces de puzzle ( /!\ l'ordre compte /!\ )
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Manager - Puzzle")
		TArray<class ASheet*> PuzzlePiecesList;
	// Montre le widget dès le begin play ?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Manager - Puzzle")
		bool ShowPuzzleWidgetAtStart = false;


protected:
	// Liste des éléments récupérés
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		TArray<bool> PuzzlePiecesFoundList;
	// Widget du puzzle
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		class UPuzzleWidget* PuzzleWidget;
	// Puzzle ouvert ?
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		bool IsPuzzleWidgetOpened = false;

	// METHODS
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Initialisation
	UFUNCTION(BlueprintCallable)
		void Init();


	// Gestion du widget
	UFUNCTION(BlueprintCallable)
		void ShowHidePuzzle();
	// Affiche le widget
	UFUNCTION(BlueprintCallable)
		void ShowPuzzle();
	// Enlève le widget
	UFUNCTION(BlueprintCallable)
		void HidePuzzle();


	// Mise à jour des pièces de puzzle sur le widget
	UFUNCTION(BlueprintCallable)
		void PuzzleUpdate();
	// Pièce de puzzle trouvée
	UFUNCTION(BlueprintCallable)
		bool FoundPuzzlePiece(class ASheet* NewPuzzlePiece);
	// Vérifie si toutes les pièces ont été trouvées
	UFUNCTION(BlueprintCallable)
		bool PuzzleIsCompleted();
	// Compte toutes les pièces trouvées jusqu'à présent
	UFUNCTION(BlueprintCallable)
		int PuzzlePiecesFoundCount();
	// Compte toutes les pièces enregistrées
	UFUNCTION(BlueprintCallable)
		int PuzzlePiecesTotalCount();

	// Event appelé lorsque qu'une pièce est trouvée
	UFUNCTION(BlueprintImplementableEvent, Category = "Manager Functions")
		void OnPuzzlePieceFound(int NbPuzzlePiecesFound);
	// Event appelé lorsque le puzzle est complété
	UFUNCTION(BlueprintImplementableEvent, Category = "Manager Functions")
		void OnPuzzleComplete();
};

