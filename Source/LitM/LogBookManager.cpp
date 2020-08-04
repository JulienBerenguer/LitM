// Fill out your copyright notice in the Description page of Project Settings.


#include "LogBookManager.h"
#include "Sheet.h"
#include "KeyObject.h"
#include "TapeRecorder.h"

// Sets default values
ALogBookManager::ALogBookManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALogBookManager::BeginPlay()
{
	Super::BeginPlay();

	// Initialisation
	Init();
}

// Called every frame
void ALogBookManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Debug
	if (DebugPrintLists) PrintList();
}

void ALogBookManager::Init() {
	// Remove NULL pointers
	SheetList.Remove(nullptr);
	TapeRecorderList.Remove(nullptr);
	KeyList.Remove(nullptr);
	ItemList.Remove(nullptr);


	// Init les listes d'éléments trouvés
	SheetFoundList.Init(false, SheetList.Num());
	TapeRecorderFoundList.Init(false, TapeRecorderList.Num());
	KeyFoundList.Init(false, KeyList.Num());
	ItemFoundList.Init(false, ItemList.Num());
}

void ALogBookManager::PrintList() {
	UE_LOG(LogTemp, Warning, TEXT("------------------ Logbook manager ------------------"));

	// Sheets
	for (auto& Itr : SheetList)
	{
		UE_LOG(LogTemp, Warning, TEXT("SheetList : %s"), *Itr->GetName());
	}
	for (auto& Itr : SheetFoundList)
	{
		UE_LOG(LogTemp, Warning, TEXT("SheetFoundList : %d"), Itr);
	}
	// Tape Recorders
	for (auto& Itr : TapeRecorderList)
	{
		UE_LOG(LogTemp, Warning, TEXT("TapeRecorderList : %s"), *Itr->GetName());
	}
	for (auto& Itr : TapeRecorderFoundList)
	{
		UE_LOG(LogTemp, Warning, TEXT("TapeRecorderFoundList : %d"), Itr);
	}
	// Keys
	for (auto& Itr : KeyList)
	{
		UE_LOG(LogTemp, Warning, TEXT("KeyList : %s"), *Itr->GetName());
	}
	for (auto& Itr : KeyFoundList)
	{
		UE_LOG(LogTemp, Warning, TEXT("KeyFoundList : %d"), Itr);
	}
	// Items
	for (auto& Itr : ItemList)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemList : %s"), *Itr->GetName());
	}
	for (auto& Itr : ItemFoundList)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemFoundList : %d"), Itr);
	}

	UE_LOG(LogTemp, Warning, TEXT("-----------------------------------------------------"));
}

void ALogBookManager::AddToList(AInteractible* NewItem) {
	if (IsValid(NewItem)) {
		// Cast
		ASheet* NewSheet = Cast<ASheet>(NewItem);
		ATapeRecorder* NewTapeRecorder = Cast<ATapeRecorder>(NewItem);
		AKeyObject* NewKey = Cast<AKeyObject>(NewItem);
		AItem* NewItems = Cast<AItem>(NewItem);

		// If cast worked => It's an item
		if (IsValid(NewItems)) {

			// Boucle pour ajouter l'item si valide
			for (int32 Index = 0; Index != ItemList.Num(); ++Index)
			{
				// Pièce valide
				if (IsValid(ItemList[Index])) {
					// Item identique ?
					if (ItemList[Index] == NewItems) {
						// Mise à jour de la liste des items trouvés
						ItemFoundList[Index] = true;
					}
				}
			}
		}

		// If cast worked => It's a Sheet
		if (IsValid(NewSheet)) {

			// Boucle pour ajouter l'item si valide
			for (int32 Index = 0; Index != SheetList.Num(); ++Index)
			{
				// Pièce valide
				if (IsValid(SheetList[Index])) {
					// Item identique ?
					if (SheetList[Index] == NewSheet) {
						// Mise à jour de la liste des items trouvés
						SheetFoundList[Index] = true;
					}
				}
			}
		}
		// If cast worked => It's a Tape Recorder
		else if (IsValid(NewTapeRecorder)) {

			// Boucle pour ajouter l'item si valide
			for (int32 Index = 0; Index != TapeRecorderList.Num(); ++Index)
			{
				// Pièce valide
				if (IsValid(TapeRecorderList[Index])) {
					// Item identique ?
					if (TapeRecorderList[Index] == NewTapeRecorder) {
						// Mise à jour de la liste des items trouvés
						TapeRecorderFoundList[Index] = true;
					}
				}
			}
		}
		// If cast worked => It's a Key
		else if (IsValid(NewKey)) {

			// Boucle pour ajouter l'item si valide
			for (int32 Index = 0; Index != KeyList.Num(); ++Index)
			{
				// Pièce valide
				if (IsValid(KeyList[Index])) {
					// Item identique ?
					if (KeyList[Index] == NewKey) {
						// Mise à jour de la liste des items trouvés
						KeyFoundList[Index] = true;
					}
				}
			}
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("LogbookManager : Not an autorized item to add"));
		}

	}

}

