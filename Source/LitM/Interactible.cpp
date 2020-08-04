// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactible.h"
#include "LitMCharacter.h"
#include "LogBookManager.h"	
#include "UObject/UObjectIterator.h"

// Sets default values
AInteractible::AInteractible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractible::BeginPlay()
{
	Super::BeginPlay();
	
	// Initialisation du Logbook Manager
	int NbLogbookManagerFind = 0;
	for (TObjectIterator<ALogBookManager> Itr; Itr; ++Itr)
	{
		if (Itr->IsA(ALogBookManager::StaticClass()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Interactible.cpp : LogbookManager found : '%s'"), *Itr->GetName());
			LogBook = *Itr;
			NbLogbookManagerFind++;
		}
	}

	if (NbLogbookManagerFind == 0) UE_LOG(LogTemp, Warning, TEXT("Interactible.cpp : No LogbookManager found"));
	if (NbLogbookManagerFind > 1) UE_LOG(LogTemp, Warning, TEXT("Interactible.cpp : Multiple LogbookManager found, total : %d"), NbLogbookManagerFind);
}

// Called every frame
void AInteractible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}


void AInteractible::OnInteraction()
{
	// Add to Logbook
	AddToLogbook();

	// Call OnInteraction BP event
	OnInteraction_BP();
}



void AInteractible::OnInteraction_BP_Implementation()
{
}


void AInteractible::LookAtActor()
{
	OnLookAtActor();
}

void AInteractible::NotLookAtActor()
{
	OnNotLookAtActor();
}

void AInteractible::AddToLogbook() {
	// A logbook is in the level ?
	if (IsValid(LogBook)) {
		// Add the object in logbook
		LogBook->AddToList(this);
	}
}