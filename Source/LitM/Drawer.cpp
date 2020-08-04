// Fill out your copyright notice in the Description page of Project Settings.


#include "Drawer.h"
#include "KeyObject.h"
#include "LitMCharacter.h"	
//#include "Components/ChildActorComponent.h"
#include "Item.h"
#include "Kismet/KismetMathLibrary.h"
//#include "Engine/StaticMesh.h"


ADrawer::ADrawer() {
	//Super::AFurniture();

	// Origine de la translation (sur l'ObjectMesh)
	TranslationOrigin = ObjectMesh->GetRelativeLocation();

	// Point d'attache
	//ItemChildActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("ItemChildActor"));
	//ItemChildActor->AttachTo(ObjectMesh);
	ItemScene = CreateDefaultSubobject<USceneComponent>(TEXT("ItemScene"));
	ItemScene->AttachTo(ObjectMesh);
}

// Called when the game starts or when spawned
void ADrawer::BeginPlay()
{
	Super::BeginPlay();

	// Attache un objet al�atoire dans le tiroir (peut �tre override par un appel dans une class Wardrobe pour y placer un item)
	// Actor al�atoire
	int ActorIndexSelected = UKismetMathLibrary::RandomIntegerInRange(0, ActorList.Num() - 1);
	// Si l'index est dans le tableau
	if (ActorList.IsValidIndex(ActorIndexSelected)) {
		UE_LOG(LogTemp, Warning, TEXT("Drawer.cpp : Actor index selected = %d"), ActorIndexSelected);
		// Actor valide (non null)
		UE_LOG(LogTemp, Warning, TEXT("Drawer.cpp : Actor valid"));
		if (IsValid(ActorList[ActorIndexSelected])) {
			// Cr�� l'actor et l'attache (tout en lui assignant ce tiroir en owner)
			UE_LOG(LogTemp, Warning, TEXT("Drawer.cpp : Actor attached"));
			AActor* NewActor = GetWorld()->SpawnActor(ActorList[ActorIndexSelected]);
			NewActor->SetOwner(this);
			AttachActor(NewActor);
		}
		// Actor non valide => pas de cr�ation
		UE_LOG(LogTemp, Warning, TEXT("Drawer.cpp : Actor non-valid"));
	}
}

bool ADrawer::AttachActor(AActor* ItemToAdd) {
	// Ajoute un item
	if (IsValid(ItemToAdd)) {
		// Destroy previous item if already had one
		if (IsValid(Item)) {
			// Item already in drawer IS NOT from Item class => destroy it
			if (!UKismetMathLibrary::ClassIsChildOf(Item->StaticClass(), AItem::StaticClass())) {
				Item->Destroy();
			}
			// Item already in drawer IS NOT from Item class => keep it
			else return false;
		}
		// Add the new item
		Item = ItemToAdd;
		Item->AttachToComponent(ItemScene, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true));
		UE_LOG(LogTemp, Warning, TEXT("Drawer.cpp : Item attached"));
		return true;
	}

	return false;
	/*// Ajoute un item
	if (IsValid(Item)) {
		ItemChildActor->SetChildActorClass(nullptr);
		ItemChildActor->CreateChildActor();
		Item->AttachToComponent(ItemChildActor, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}*/
}

/*// Called every frame
void ADrawer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FurnitureAction(DeltaTime);
}*/

void ADrawer::FurnitureAction(float DeltaTime)
{
	Super::FurnitureAction(DeltaTime);

	// Translation
	TranslationAction(TranslationOrigin, TranslationEnd, DeltaTime);
}
