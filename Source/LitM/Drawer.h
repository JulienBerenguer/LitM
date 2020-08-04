// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Furniture.h"
#include "Drawer.generated.h"

/**
 * 
 */
UCLASS()
class LITM_API ADrawer : public AFurniture
{
	GENERATED_BODY()

public:
	ADrawer();

	// COMPONENTS
public:
	// Point d'attache des objets dans les tiroirs
	//UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		//class UChildActorComponent* ItemChildActor;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		USceneComponent* ItemScene;


	// VARIABLES
public:
	// Translation : Valeur d'arrivée
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Drawer")
		FVector TranslationEnd = FVector(50.0f, 0.0f, 0.0f);

	// Liste d'objets à ajouter aux tiroirs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Drawer")
		TArray<TSubclassOf<AActor>> ActorList;
	//class UStaticMesh*

protected:
	// Translation : Valeur de départ
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Object Options - Private")
		FVector TranslationOrigin;
	// Item géré par le drawer (n'est pas dans un ChildActor pour simplifier la mise en scène)
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Object Options - Private")
		AActor* Item;

	// METHODS
public:
	virtual void FurnitureAction(float DeltaTime) override;
	// Remplace un item
	UFUNCTION(BlueprintCallable, Category = "Object Functions")
		bool AttachActor(AActor* ItemToAdd);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
/*public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;*/
};
