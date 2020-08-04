// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyObject.h"
#include "LitMCharacter.h"

// Called when the game starts or when spawned
void AKeyObject::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void AKeyObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKeyObject::OnInteraction()
{
	Super::OnInteraction();

	UE_LOG(LogTemp, Warning, TEXT("KEY"));

	// Add the key to player inventory
	Cast<ALitMCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn())->AddKey(GetUniqueID());

	// If boolean enabled, destroy the item
	DestroyIt(DestroyIfUsed);

}

// Destruction of the item
void AKeyObject::DestroyIt(bool NewDestroyIfUsed) {
	// Destroy item if boolean enabled
	if (NewDestroyIfUsed) {
		// SEE BLUEPRINT
		// Don't destroy it or else doors won't have the name displayed
		OnDestroy();	// Blueprint Event
	}
}