// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleWidget.h"


void UPuzzleWidget::HidePuzzlePieces() {
	// Liste toutes les images des pièces
	for (UImage* PuzzlePieceImage : PuzzlePiecesImageList)
	{
		// Cache la pièce
		PuzzlePieceImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPuzzleWidget::DisplayPuzzlePiece(int PuzzlePieceIndex) {
	// Si l'index existe
	if (PuzzlePiecesImageList.IsValidIndex(PuzzlePieceIndex)) {
		// Met à jour la visibilité de la pièce
		PuzzlePiecesImageList[PuzzlePieceIndex]->SetVisibility(ESlateVisibility::Visible);
	}
}