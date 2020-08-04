// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Furniture.h"
#include "Door.generated.h"

/**
 * 
 */
UCLASS()
class LITM_API ADoor : public AFurniture
{
	GENERATED_BODY()

public:
	ADoor();

	// VARIABLES
public:
	// Rotation : Valeur d'arrivée
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Door", meta = (UIMin = -180.0f, UIMax = 180.0f))
		float RotationEnd = 90.0f;

protected:
	// Rotation : Valeur de départ
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Object Options - Private")
		float RotationOrigin;

	// METHODS
public:
	virtual void FurnitureAction(float DeltaTime) override;

/*public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;*/
	
};
