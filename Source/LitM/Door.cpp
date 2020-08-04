// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "KeyObject.h"
#include "LitMCharacter.h"

ADoor::ADoor() {
	//Super::AFurniture();

	// Origine de la rotation Z (sur l'ObjectMesh), en principe 0.0f
	RotationOrigin = ObjectMesh->GetRelativeRotation().Yaw;
}

/*// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FurnitureAction(DeltaTime);
}*/

void ADoor::FurnitureAction(float DeltaTime)
{
	Super::FurnitureAction(DeltaTime);

	// Rotation sur l'axe Z (Yaw)
	FRotator AngleOrigin = FRotator(0.0f, RotationOrigin, 0.0f);
	FRotator AngleEnd = FRotator(0.0f, RotationEnd, 0.0f);
	RotationAction(AngleOrigin, AngleEnd, DeltaTime);

}


