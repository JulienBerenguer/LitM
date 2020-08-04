// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleWidget.h"


void UPuzzleWidget::HidePuzzlePieces() {
	// Liste toutes les images des pi�ces
	for (UImage* PuzzlePieceImage : PuzzlePiecesImageList)
	{
		// Cache la pi�ce
		PuzzlePieceImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPuzzleWidget::DisplayPuzzlePiece(int PuzzlePieceIndex) {
	// Si l'index existe
	if (PuzzlePiecesImageList.IsValidIndex(PuzzlePieceIndex)) {
		// Met � jour la visibilit� de la pi�ce
		PuzzlePiecesImageList[PuzzlePieceIndex]->SetVisibility(ESlateVisibility::Visible);
	}
}