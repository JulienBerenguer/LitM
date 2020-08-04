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
	// Son à écouter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Tape Recorder")
		USoundBase* Audio = nullptr;
protected:
	// Gestion des sons d'event (ouverture, fermeture, objet verrouillé, ...)
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Object Options - Private")
		USoundManager* Sound = nullptr;
	// Est-ce que le magnétophone est en pause ?
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Object Options - Private")
		bool IsPaused = false;

	// METHODES
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Event son qui démarre
	UFUNCTION(BlueprintImplementableEvent, Category = "TapeRecorder")
		void OnSoundStart();

	// Event son qui redémarre
	UFUNCTION(BlueprintImplementableEvent, Category = "TapeRecorder")
		void OnSoundPlay();

	// Event son qui s'arrête
	UFUNCTION(BlueprintImplementableEvent, Category = "TapeRecorder")
		void OnSoundStop();

	// Event son de tous les autres magnétos qui s'arrêtent
	UFUNCTION(BlueprintImplementableEvent, Category = "TapeRecorder")
		void OnSoundAnotherTapeStop();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Override de la fonction d'interaction
	virtual void OnInteraction() override;

	// Destruction of the item
	virtual void DestroyIt(bool NewDestroyIfUsed) override;
};
