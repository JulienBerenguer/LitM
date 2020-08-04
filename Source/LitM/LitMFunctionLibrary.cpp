// Fill out your copyright notice in the Description page of Project Settings.


#include "LitMFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "LitMSaveGame.h"
#include "LitMGameInstance.h"

// Tuto save game in C++ : https://www.youtube.com/watch?v=jkfbzt8etws
//						   https://docs.unrealengine.com/en-US/Gameplay/SaveGame/index.html

// Test
void ULitMFunctionLibrary::TestLitMLibrary() {

}

// Get the game instance
ULitMGameInstance* ULitMFunctionLibrary::GetGameInstance(const UObject* WorldContextObject) {
	// Get GameInstance
	ULitMGameInstance* GameInstance = Cast<ULitMGameInstance>(GEngine->GetWorldFromContextObject(WorldContextObject)->GetGameInstance());
	return GameInstance;
}

/*// Get the save game
ULitMSaveGame* ULitMFunctionLibrary::LoadSave(const UObject* WorldContextObject) {
	
	// Get a save game
	ULitMSaveGame* SaveGame = Cast<ULitMSaveGame>(UGameplayStatics::CreateSaveGameObject(ULitMSaveGame::StaticClass()));
	// Get GameInstance
	ULitMGameInstance* GameInstance = GetGameInstance(WorldContextObject);
	if (IsValid(GameInstance)) {
		// Load from slot
		ULitMSaveGame* SaveGameFromSlot = Cast<ULitMSaveGame>(UGameplayStatics::LoadGameFromSlot(GameInstance->SaveGameName, 0));
		if (IsValid(SaveGameFromSlot)) {
			// Return the loaded save
			return SaveGameFromSlot;
		}
		else {
			// Return a new save
			return SaveGame;
		}
	}
	//GameInstance not found, return a new save
	return SaveGame;

}

// Save the game (after modifications from LoadGame)
bool ULitMFunctionLibrary::SaveGame(const UObject* WorldContextObject, ULitMSaveGame* SaveGame) {
	// Get GameInstance
	ULitMGameInstance* GameInstance = GetGameInstance(WorldContextObject);
	if (IsValid(GameInstance)) {
		if (!IsValid(SaveGame)) {
			// The save game loaded isn't found => create a new one (values by default)
			ULitMSaveGame* SaveGame = Cast<ULitMSaveGame>(UGameplayStatics::CreateSaveGameObject(ULitMSaveGame::StaticClass()));
		}
		// Save the game
		UGameplayStatics::SaveGameToSlot(SaveGame, GameInstance->SaveGameName, 0);
		return true;
	}
	// Save failed (GameInstance not found)
	return false;
}*/

/*// Get GameInstance
	ULitMGameInstance* GameInstance = GetGameInstance();
	if (IsValid(GameInstance)) {
		// Load the save game
		ULitMSaveGame* SaveGame = LoadSave();
		if (!IsValid(SaveGame)) {
			// Load don't find a save => create a new save
			SaveGame = Cast<ULitMSaveGame>(UGameplayStatics::CreateSaveGameObject(ULitMSaveGame::StaticClass()));
		}
		// Save the game
		UGameplayStatics::SaveGameToSlot(SaveGame, GameInstance->SaveGameName, 0);
		return true;
	}
	// Save failed (GameInstance or SaveGame not found)
	return false;*/