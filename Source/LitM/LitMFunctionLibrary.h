// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LitMFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class LITM_API ULitMFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	// METHODS
public:
	// Test
	UFUNCTION(BlueprintCallable, Category = "Litm Library")
		static void TestLitMLibrary();
	// Get the game instance
	UFUNCTION(BlueprintCallable, Category = "Litm Library")
		class ULitMGameInstance* GetGameInstance(const UObject* WorldContextObject);
	/*// Get the save game
	UFUNCTION(BlueprintCallable, Category = "Litm Library")
		static class ULitMSaveGame* LoadSave(const UObject* WorldContextObject);
	// Save the game (after modifications from LoadGame)
	UFUNCTION(BlueprintCallable, Category = "Litm Library")
		static bool SaveGame(const UObject* WorldContextObject, ULitMSaveGame* SaveGame);*/

};
