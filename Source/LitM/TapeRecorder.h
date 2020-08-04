// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "SoundManager.h"
#include "TapeRecorder.generated.h"

/**
 * 
 */
UCLASS()
class LITM_API ATapeRecorder : public AItem
{
	GENERATED_BODY()

	// VARIABLES
public:
	// Son � �couter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Tape Recorder")
		USoundBase* Audio = nullptr;
protected:
	// Gestion des sons d'event (ouverture, fermeture, objet verrouill�, ...)
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Object Options - Private")
		USoundManager* Sound = nullptr;
	// Est-ce que le magn�tophone est en pause ?
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Object Options - Private")
		bool IsPaused = false;

	// METHODES
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Event son qui d�marre
	UFUNCTION(BlueprintImplementableEvent, Category = "TapeRecorder")
		void OnSoundStart();

	// Event son qui red�marre
	UFUNCTION(BlueprintImplementableEvent, Category = "TapeRecorder")
		void OnSoundPlay();

	// Event son qui s'arr�te
	UFUNCTION(BlueprintImplementableEvent, Category = "TapeRecorder")
		void OnSoundStop();

	// Event son de tous les autres magn�tos qui s'arr�tent
	UFUNCTION(BlueprintImplementableEvent, Category = "TapeRecorder")
		void OnSoundAnotherTapeStop();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Override de la fonction d'interaction
	virtual void OnInteraction() override;

	// Destruction of the item
	virtual void DestroyIt(bool NewDestroyIfUsed) override;
};
