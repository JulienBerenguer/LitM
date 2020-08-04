// Fill out your copyright notice in the Description page of Project Settings.


#include "Switch.h"
#include "KeyObject.h"
#include "LitMCharacter.h"


ASwitch::ASwitch() {
	// Button basement
	ObjectMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectMesh2"));
	ObjectMesh2->AttachTo(RotationScene);

	// Origine de la translation (sur l'ObjectMesh)
	TranslationOrigin = ObjectMesh->GetRelativeLocation();

	// Origine de la rotation Z (sur l'ObjectMesh), en principe 0.0f
	RotationOrigin = ObjectMesh->GetRelativeRotation();
}

// Called when the game starts or when spawned
void ASwitch::BeginPlay()
{
	Super::BeginPlay();

	// Init lights
	OnInteraction();
}

void ASwitch::OnInteraction()
{
	// > Changement de lumi�re
	UE_LOG(LogTemp, Warning, TEXT("LightSwitch  : %d"), IsActive);

	// V�rification avant utilisation
	// Si d�verrouill�
	if (!IsLocked) {
		// Si objet n'est pas utilis�
		if (!IsUsed) {

			// Activation / D�sactivation des lumi�res (actor)
			for (ALight* Light : LightList)
			{
				if (Light != nullptr) Light->SetEnabled(IsActive);
			}
			// Activation / D�sactivation des lumi�res (component)
			for (ULightComponent* LightComponent : LightComponentList)
			{
				if (LightComponent != nullptr) LightComponent->SetVisibility(IsActive);
			}
			IsActive = !IsActive;
		}
	}

	// > Translation du bouton
	// Do Once / init
	if (!DoFurnitureInteraction) {
		DoFurnitureInteraction = true;

		// Si interrupteur d�j� activ�, alors inversion de la translation et met le bouton � a translation de fin
		if (!IsActive) {
			// Prise en compte du type de mouvement
			if (ActionType == EActionType::Translation) {
				OpeningDirection = !OpeningDirection;
				ObjectMesh->SetRelativeLocation(TranslationEnd);
			}
			else if (ActionType == EActionType::Rotation) {
				OpeningDirection = !OpeningDirection;
				ObjectMesh->SetRelativeRotation(RotationEnd);
			}
		}
	}
	// InGame => appel d'OnInteraction() de Furniture et du FurnitureInteraction(), celui du Drawer (translation)
	else Super::OnInteraction();
}


void ASwitch::FurnitureAction(float DeltaTime)
{
	Super::FurnitureAction(DeltaTime);

	// Translation
	if (ActionType == EActionType::Translation) {
		TranslationAction(TranslationOrigin, TranslationEnd, DeltaTime);
	}
	// Rotation
	else if (ActionType == EActionType::Rotation) {
		RotationAction(RotationOrigin, RotationEnd, DeltaTime);
	}

}

