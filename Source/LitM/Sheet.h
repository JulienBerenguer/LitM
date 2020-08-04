// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SheetStructs.h"
#include "Interactible.h"
#include "Item.h"
#include "Sheet.generated.h"

/**
 * 
 */
UCLASS()
class LITM_API ASheet : public AItem
{
	GENERATED_BODY()

public:
	ASheet();

	// COMPONENTS
public:
	// RootScene
	/*UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		USceneComponent* RootScene;*/
	// Widget
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		UWidgetComponent* Widget;
	// Box Collider => pour que le OnInteraction() agisse, le raycast passant à travers le widget 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		UBoxComponent* Collider;

	// VARIABLES
public:
	// Détruit la feuille si utilisé
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Sheet")
		bool DestroyIfUsed = false;*/
	// Cache le texte sur la scène ? L'affiche quand même en widget quand le joueur inteéragit avec
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Sheet")
		bool HideTextOnScene = false;
	// Widget à utiliser
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Sheet")
		TSubclassOf<class USheetWidget> WidgetClass;
	// Texte de la feuille
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Sheet")
		FDataTableRowHandle Text;
	// Texte de la feuille
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Sheet")
		UDataTable* Style;
	// Image de fond de la feuille
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Sheet")
		UTexture2D* BackgroundTexture;
	// Image de fond de la feuille
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Sheet")
		bool BackgroundTextureMatchSize = true;


protected :
	// Feuille de carnet de notes telle qu'elle apparaît dans la scène
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		class USheetWidget* SceneSheetWidget;
	// Feuille de carnet de notes telle qu'elle apparaît lorsque le joueur s'en sert
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		class USheetWidget* ShowSheetWidget;
	// Widget bien initialisé
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		bool IsInit = false;

	// Est-ce que la feuille peut être utilisée ?
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		bool CanBeUsed = true;

	// Lien au puzzle si est une pièce de puzzle, est une feuille s'il est à NULL
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		class APuzzleManager* Puzzle = nullptr;


	// METHODS
public:
	// Override de la fonction d'interaction
	virtual void OnInteraction() override;
	// Fonction d'initialisation
	bool InitSheet();
	// Initialise le puzzle si est une pièce de puzzle
	void InitPuzzle(class APuzzleManager* NewPuzzle);
	// Détruit si utilisé lorsque l'option est activée
	//void DestroySheet(bool NewDestroyIfUsed);
	// Destruction of the item
	virtual void DestroyIt(bool NewDestroyIfUsed) override;
	// Renvoie la SheetWidget à afficher | true = ShowSheetWidget | false = SceneSheetWidget
	class USheetWidget* GetSheetWidget(bool Type = true);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
