// Fill out your copyright notice in the Description page of Project Settings.


#include "TapeRecorder.h"
#include "EngineUtils.h"
#include "UObject/UObjectIterator.h"

// Called when the game starts or when spawned
void ATapeRecorder::BeginPlay()
{
	Super::BeginPlay();

	// Initialisation du Sound Manager => /!\ Doit être dans le BeginPlay pour fonctionner et non dans le constructeur
	Sound = NewObject<USoundManager>(this, TEXT("Sound"));
}

// Called every frame
void ATapeRecorder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATapeRecorder::OnInteraction()
{
	Super::OnInteraction();

	UE_LOG(LogTemp, Warning, TEXT("TAPE RECORDER"));

	// Stop all tape recorder sound
	for (TActorIterator<ATapeRecorder> Itr(GetWorld()); Itr; ++Itr)
	{
		// Iterator is an ATapeRecorder
		if (Itr->IsA(ATapeRecorder::StaticClass()))
		{
			// Cast to ATapeRecorder
			ATapeRecorder* TapeRecorderFound = Cast<ATapeRecorder>(*Itr);
			// Debug
			UE_LOG(LogTemp, Warning, TEXT("TapeRecorder.cpp : TapeRecorder found : '%s'"), *TapeRecorderFound->GetName());
			// If had an Sound UObject, destroy the audio (IsValid() needed, the iterator can return an uninitialised item)
			if (IsValid(TapeRecorderFound->Sound)) {
				// Same recorder
				if (TapeRecorderFound == this) {
					UE_LOG(LogTemp, Warning, TEXT("TapeRecorder.cpp : > Same TapeRecorder"), *Itr->GetName());
					// Had sound => Same recorder used
					if (Sound->HadSound()) {
						// Sound is playing
						if (Sound->IsPlaying()) {
							OnSoundStop();		// Event BP
							//Sound->StopSound();	// Stop it => /!\ seems to destroy audio variable, next HadSound() return false
							UE_LOG(LogTemp, Warning, TEXT("TapeRecorder.cpp : >> Stop"), *Itr->GetName());
						}
						// Sound is stopped
						else {
							OnSoundPlay();		// Event BP
							//Sound->PlaySound(); // Play it again
							UE_LOG(LogTemp, Warning, TEXT("TapeRecorder.cpp : >> Play"), *Itr->GetName());
						}
					}
					// Hasn't audio variable => New recorder used
					else {
						// Play actual tape recorder sound
						if (Audio != nullptr) {
							OnSoundStart();				// Event BP
							//Sound->StartSound(Audio);	// Start sound
						}
						UE_LOG(LogTemp, Warning, TEXT("TapeRecorder.cpp : >> Start"), *Itr->GetName());
					}
				}
				// Another recorder
				else {
					OnSoundAnotherTapeStop();					// Event BP
					TapeRecorderFound->Sound->DestroySound();	// Stop sound and destroy the audio variable
				}
			}
		}
	}


	// If boolean enabled, destroy the item
	DestroyIt(DestroyIfUsed);
}

// Destruction of the item
void ATapeRecorder::DestroyIt(bool NewDestroyIfUsed) {
	// Destroy item if boolean enabled
	if (NewDestroyIfUsed) {
		// SEE BLUEPRINT
		// Don't destroy it or else doors won't have the name displayed
		OnDestroy();	// Blueprint Event
	}
}