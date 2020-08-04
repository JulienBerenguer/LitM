// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Components/AudioComponent.h"
#include "LitMGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LITM_API ULitMGameInstance : public UGameInstance
{
	GENERATED_BODY()

	// VARIABLES
public:
	// Nom de la savegarde à utiliser
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString SaveGameName = "LitMSave";

	// Liste audio - Voix
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UAudioComponent*> ListVoices;

	// Liste audio - Effets Sonores
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UAudioComponent*> ListSoundEffects;

	// Liste audio - Musiques
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UAudioComponent*> ListMusics;


	// METHODS
public:
	//
};
