// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Furniture.h"
#include "Wardrobe.generated.h"

/**
 * 
 */
UCLASS()
class LITM_API AWardrobe : public AFurniture
{
	GENERATED_BODY()
public:
	AWardrobe();

		// VARIABLES
public:
	/*// R�f�rence de la cl� si verrouill� (si non-verrouill�, alors ne pas mettre de cl�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Wardrobe")
		TSubclassOf<AInteractible> NewItemToAdd;
	// Item name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Wardrobe")
		FString ItemName = "";
	// Item description
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Wardrobe")
		FString ItemDescription = "";*/
protected:
	// Child actors list
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Object Options - Private")
		TArray<AActor*> ChildActorList;
	// Child actors drawer list
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Object Options - Private")
		TArray<class ADrawer*> ChildActorDrawerList;

	// METHODS
public:
	// Add the item to an drawer
	//void AddItem();
	void AddItemInRandomDrawer(AActor* ItemToAdd);
	// Get the wardrobe drawers
	void GetAllDrawers();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
