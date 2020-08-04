// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactible.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS()
class LITM_API AItem : public AInteractible
{
	GENERATED_BODY()

	// CONSTRUCTOR
public:
	AItem();

	// VARIABLES
public:
	// Call the destruction method if enabled when the player use it
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Item")
		bool DestroyIfUsed = false;
	// Place the item in a wardrobe drawer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Item")
		class AWardrobe* WardrobeToLink = nullptr;

	// COMPONENTS
public:
	// Mesh
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		class UStaticMeshComponent* ObjectMesh;
	// Rotation Point
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		class USceneComponent* RootScene;

	// METHODS
public:
	// Destruction of the item
	UFUNCTION(BlueprintCallable, Category = "Object Functions")
		virtual void DestroyIt(bool NewDestroyIfUsed);
	// Destruction Event
	UFUNCTION(BlueprintImplementableEvent, Category = "Object Functions")
		void OnDestroy();

	// Override de la fonction d'interaction
	virtual void OnInteraction() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
