// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "KeyObject.generated.h"

/**
 * 
 */
UCLASS()
class LITM_API AKeyObject : public AItem
{
	GENERATED_BODY()

	// METHODES
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Override de la fonction d'interaction
	virtual void OnInteraction() override;

	// Destruction of the item
	virtual void DestroyIt(bool NewDestroyIfUsed) override;
};
