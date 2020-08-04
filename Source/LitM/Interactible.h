// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Interactible.generated.h"

UCLASS()
class LITM_API AInteractible : public AActor
{
	GENERATED_BODY()

	// CONSTRUCTOR
public:	
	// Sets default values for this actor's properties
	AInteractible();

	// VARIABLES
public:
	// Object name (example : keys and doors, LookAtActor() Item event)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - General")
		FString Name = "";
	// Object description (example : keys for logbook)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - General")
		FString Description = "";

protected:
	// Gestionnaire du journal de bord
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		class ALogBookManager* LogBook;

	// METHODS
public:
	UFUNCTION(BlueprintCallable, Category = "Interaction")
		virtual void OnInteraction();

	UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
		void OnInteraction_BP();

	// Event when the player look at the actor
	UFUNCTION(BlueprintImplementableEvent, Category = "Object Functions")
		void OnLookAtActor();

	// Function to call OnLookAtActor() event
	UFUNCTION(BlueprintCallable, Category = "Object Functions")
		void LookAtActor();

	// Event when the player DON'T look at the actor
	UFUNCTION(BlueprintImplementableEvent, Category = "Object Functions")
		void OnNotLookAtActor();

	// Function to call OnNotLookAtActor() event
	UFUNCTION(BlueprintCallable, Category = "Object Functions")
		void NotLookAtActor();

	// Function to call OnNotLookAtActor() event
	UFUNCTION(BlueprintCallable, Category = "Object Functions")
		void AddToLogbook();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
