// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SheetWidget.h"
#include "Components/Image.h"
#include "PuzzleWidget.generated.h"

/**
 * 
 */
UCLASS()
class LITM_API UPuzzleWidget : public UUserWidget
{
	GENERATED_BODY()

	// VARIABLES
public:
	// Liste des images des pi�ces de puzzle ( /!\ l'ordre compte /!\ )
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget - Puzzle")
		TArray<class UImage*> PuzzlePiecesImageList;

	// METHODES
public:
	// Cache chaque pi�ce (� appeler dans le BeginPlay() du blueprint)
	UFUNCTION(BlueprintCallable)
		void HidePuzzlePieces();

	// Affiche une pi�ce
	UFUNCTION(BlueprintCallable)
		void DisplayPuzzlePiece(int PuzzlePieceIndex);
};
