// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundManager.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"

USoundManager::USoundManager() {

}

bool USoundManager::StartSound(USoundBase* NewAudio, class UAudioComponent*& OutAudio) {
	// Ajoute un audio, puis le démarre
	if (IsValid(NewAudio)) {
		// Détruit l'ancien audio
		DestroySound();
		// En créé un nouveau
		Audio = UGameplayStatics::CreateSound2D(GetWorld(), NewAudio, 1.0f, 1.0f, 0.0f, nullptr, false, true);
		if (IsValid(Audio)) {
			// Le lance
			Audio->Play();
			Audio->SetVolumeMultiplier(VolumeMultiplier);
			OutAudio = Audio;
			return true;
		}
	}
	//Audio->OnAudioFinished.AddDynamic(this, &USoundManager::StopSound);
	//UE_LOG(LogTemp, Warning, TEXT("> SoundManager.cpp : StartSound => NewAudio = %d | Audio = %d"), IsValid(NewAudio), IsValid(Audio));
	return false;
}

bool USoundManager::PlaySound() {
	// Relance l'audio
	if (IsValid(Audio)) {
		Audio->Play();
		Audio->SetVolumeMultiplier(VolumeMultiplier);
		return true;
	}
	else return false;
}

bool USoundManager::StopSound() {
	// Stoppe l'audio
	if (IsValid(Audio)) {
		Audio->Stop();
		return true;
	}
	else return false;
}


bool USoundManager::DestroySound() {
	// Stoppe l'audio
	StopSound();
	// Détruit l'audio
	if (IsValid(Audio)) {
		Audio->DestroyComponent();
		return true;
	}
	else return false;
}


bool USoundManager::HadSound() {
	// Est-ce qu'il y a un audio en attente ?
	if (IsValid(Audio)) {
		return true;
	}
	else return false;
}

bool USoundManager::IsPlaying() {
	// Est-ce que l'audio est en pause ?
	if (IsValid(Audio)) {
		return Audio->IsPlaying();
	}
	else return false;
}