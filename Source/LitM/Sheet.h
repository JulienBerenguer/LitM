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
	// Box Collider => pour que le OnInteraction() agisse, le raycast passant � travers le widget 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		UBoxComponent* Collider;

	// VARIABLES
public:
	// D�truit la feuille si utilis�
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Sheet")
		bool DestroyIfUsed = false;*/
	// Cache le texte sur la sc�ne ? L'affiche quand m�me en widget quand le joueur inte�ragit avec
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Sheet")
		bool HideTextOnScene = false;
	// Widget � utiliser
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
	// Feuille de carnet de notes telle qu'elle appara�t dans la sc�ne
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		class USheetWidget* SceneSheetWidget;
	// Feuille de carnet de notes telle qu'elle appara�t lorsque le joueur s'en sert
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		class USheetWidget* ShowSheetWidget;
	// Widget bien initialis�
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		bool IsInit = false;

	// Est-ce que la feuille peut �tre utilis�e ?
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		bool CanBeUsed = true;

	// Lien au puzzle si est une pi�ce de puzzle, est une feuille s'il est � NULL
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		class APuzzleManager* Puzzle = nullptr;


	// METHODS
public:
	// Override de la fonction d'interaction
	virtual void OnInteraction() override;
	// Fonction d'initialisation
	bool InitSheet();
	// Initialise le puzzle si est une pi�ce de puzzle
	void InitPuzzle(class APuzzleManager* NewPuzzle);
	// D�truit si utilis� lorsque l'option est activ�e
	//void DestroySheet(bool NewDestroyIfUsed);
	// Destruction of the item
	virtual void DestroyIt(bool NewDestroyIfUsed) override;
	// Renvoie la SheetWidget � afficher | true = ShowSheetWidget | false = SceneSheetWidget
	class USheetWidget* GetSheetWidget(bool Type = true);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
