// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LitMSaveGame.generated.h"

/**
 * 
 */

/*USTRUCT(BlueprintType, Blueprintable)
struct LITM_API FOptionsInfos
{
	GENERATED_USTRUCT_BODY()

	// Voice
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AudioVoice = 1.0f;
	// Effets sonores
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AudioSoundEffects = 1.0f;
	// Musique
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AudioMusic = 1.0f;
	// Luminosité
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Luminosity = 1.0f;
};*/

UCLASS()
class LITM_API ULitMSaveGame : public USaveGame
{
	GENERATED_BODY()

	// VARIABLES
public:
	/*// Liste des variables du menu d'option
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FOptionsInfos OptionsInfos;*/

	// Synchronisation verticale
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Vsync = true;
	// Voice
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int AudioVoice = 2;
	// Effets sonores
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int AudioSoundEffects = 2;
	// Musique
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int AudioMusic = 2;
	// Luminosité
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Luminosity = 2;
};
