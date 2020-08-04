// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Furniture.h"
#include "Engine/Light.h"
#include "Components/LightComponent.h"
#include "Switch.generated.h"

/**
 * 
 */
UCLASS()
class LITM_API ASwitch : public AFurniture
{
	GENERATED_BODY()

public:
	ASwitch();

	// COMPONENTS
public:
	// Mesh
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		class UStaticMeshComponent* ObjectMesh2;

	// VARIABLES
public:
	// Etat de la lumière
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Switch")
		bool IsActive = true;

	// Translation : Valeur d'arrivée
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Switch")
		EActionType ActionType = EActionType::Translation;

	// Translation : Valeur d'arrivée
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Switch")
		FVector TranslationEnd = FVector(50.0f, 0.0f, 0.0f);

	// Rotation : Valeur d'arrivée
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Switch")
		FRotator RotationEnd = FRotator(0.0f, 45.0f, 0.0f);

	// Liste des lumières (actor, dans la scène)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Switch")
		TArray<ALight*> LightList;

	// Liste des lumières (component, dans le même blueprint)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Switch")
		TArray<ULightComponent*> LightComponentList;

protected:
	// Translation : Valeur de départ
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Object Options - Private")
		FVector TranslationOrigin;

	// Rotation : Valeur de départ
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Object Options - Private")
		FRotator RotationOrigin;

	// Passage d'initialisation de OnInteraction
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Object Options - Private")
		bool DoFurnitureInteraction = false;


	// METHODS
public:
	// Override de la fonction d'interaction
	virtual void OnInteraction() override;
	// Override de la fonction d'interaction - Tick
	virtual void FurnitureAction(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

/*public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;*/
};


