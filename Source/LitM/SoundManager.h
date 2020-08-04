// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SoundManager.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class LITM_API USoundManager : public UObject
{
	GENERATED_BODY()

public:
	USoundManager();

	// VARIABLES
public:
	// Référence de la clé si verrouillé (si non-verrouillé, alors ne pas mettre de clé)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Manager - Sound")
		class UAudioComponent* Audio = nullptr;
	// Son de l'audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Manager - Sound")
		float VolumeMultiplier = 1.0f;

	// METHODS
public:
	UFUNCTION(BlueprintCallable)
		bool StartSound(class USoundBase* NewAudio, class UAudioComponent*& OutAudio);
	UFUNCTION(BlueprintCallable)
		bool PlaySound();
	UFUNCTION(BlueprintCallable)
		bool StopSound();
	UFUNCTION(BlueprintCallable)
		bool DestroySound();

	UFUNCTION(BlueprintCallable)
		bool HadSound();
	UFUNCTION(BlueprintCallable)
		bool IsPlaying();
};
