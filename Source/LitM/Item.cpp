// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Wardrobe.h"

AItem::AItem(){
	// Meshs
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;
	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectMesh"));
	ObjectMesh->AttachTo(RootScene);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	// try to add the item in a wardrobe drawer
	if (IsValid(WardrobeToLink)) {
		WardrobeToLink->AddItemInRandomDrawer(this);
		UE_LOG(LogTemp, Warning, TEXT("Item.cpp : Try to add an item to a wardrobe drawer"));
	}
}


void AItem::OnInteraction()
{
	Super::OnInteraction();

	// Interaction to override
	// TODO IN CHILD CLASS

	// If boolean enabled, destroy the item
	//DestroyIt(DestroyIfUsed);

}

void AItem::DestroyIt(bool NewDestroyIfUsed) {
	// Destroy item if boolean enabled
	if (NewDestroyIfUsed) {
		OnDestroy();	// Blueprint Event
		//this->Destroy();
	}
}