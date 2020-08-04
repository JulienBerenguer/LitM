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
 * 3/ Lier ces derniers dans le tableau de pi�ces de puzzle dans l'ordre voulu
 * 4/ Lier les images du Widget qu'utilise le PuzzleManager dans -le m�me ordre- que pr�c�demment (d�voile la pi�ce par index)
 * 5/ R�glage des param�tres du PuzzleManager, des pi�ces et des Widget du PuzzleManager et des pi�ces
 */
UCLASS(BlueprintType, Blueprintable)
class LITM_API APuzzleManager : public AActor
{
	GENERATED_BODY()

public:
	APuzzleManager();

	// VARIABLES
public:
	// Widget � utiliser
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Manager - Puzzle")
		TSubclassOf<class UPuzzleWidget> WidgetClass;
	// Liste des pi�ces de puzzle ( /!\ l'ordre compte /!\ )
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Manager - Puzzle")
		TArray<class ASheet*> PuzzlePiecesList;
	// Montre le widget d�s le begin play ?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Manager - Puzzle")
		bool ShowPuzzleWidgetAtStart = false;


protected:
	// Liste des �l�ments r�cup�r�s
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
	// Enl�ve le widget
	UFUNCTION(BlueprintCallable)
		void HidePuzzle();


	// Mise � jour des pi�ces de puzzle sur le widget
	UFUNCTION(BlueprintCallable)
		void PuzzleUpdate();
	// Pi�ce de puzzle trouv�e
	UFUNCTION(BlueprintCallable)
		bool FoundPuzzlePiece(class ASheet* NewPuzzlePiece);
	// V�rifie si toutes les pi�ces ont �t� trouv�es
	UFUNCTION(BlueprintCallable)
		bool PuzzleIsCompleted();
	// Compte toutes les pi�ces trouv�es jusqu'� pr�sent
	UFUNCTION(BlueprintCallable)
		int PuzzlePiecesFoundCount();
	// Compte toutes les pi�ces enregistr�es
	UFUNCTION(BlueprintCallable)
		int PuzzlePiecesTotalCount();

	// Event appel� lorsque qu'une pi�ce est trouv�e
	UFUNCTION(BlueprintImplementableEvent, Category = "Manager Functions")
		void OnPuzzlePieceFound(int NbPuzzlePiecesFound);
	// Event appel� lorsque le puzzle est compl�t�
	UFUNCTION(BlueprintImplementableEvent, Category = "Manager Functions")
		void OnPuzzleComplete();
};

