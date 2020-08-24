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

	// Effectue la translation de départ
	ObjectMesh->SetRelativeLocation(TranslationStart);

	// Attache un objet aléatoire dans le tiroir (peut être override par un appel dans une class Wardrobe pour y placer un item)
	// Actor aléatoire
	int ActorIndexSelected = UKismetMathLibrary::RandomIntegerInRange(0, ActorList.Num() - 1);
	// Si l'index est dans le tableau
	if (ActorList.IsValidIndex(ActorIndexSelected)) {
		UE_LOG(LogTemp, Warning, TEXT("Drawer.cpp : Actor index selected = %d"), ActorIndexSelected);
		// Actor valide (non null)
		UE_LOG(LogTemp, Warning, TEXT("Drawer.cpp : Actor valid"));
		if (IsValid(ActorList[ActorIndexSelected])) {
			// Créé l'actor et l'attache (tout en lui assignant ce tiroir en owner)
			UE_LOG(LogTemp, Warning, TEXT("Drawer.cpp : Actor attached"));
			AActor* NewActor = GetWorld()->SpawnActor(ActorList[ActorIndexSelected]);
			NewActor->SetOwner(this);
			AttachActor(NewActor);
		}
		// Actor non valide => pas de création
		UE_LOG(LogTemp, Warning, TEXT("Drawer.cpp : Actor non-valid"));
	}
}

bool ADrawer::AttachActor(AActor* ItemToAdd) {
	// Ajoute un item
	if (IsValid(ItemToAdd)) {
		// Destroy previous item if already had one
		if (IsValid(Item)) {
			// Item already in drawer IS NOT from Item class => destroy it
			if (!UKismetMathLibrary::ClassIsChildOf(Item->GetClass(), AItem::StaticClass())) {
				UE_LOG(LogTemp, Warning, TEXT("Drawer.cpp : Actor attached of class '%s' is removed"), *Item->GetClass()->GetName());
				Item->Destroy();
			}
			// Item already in drawer IS NOT from Item class => keep it
			else return false;
		}
		// If the item is an AItem, then keep the world rotation and scale, if not then keep it relative (might go outside the drawer if spawn at game launch)
		EAttachmentRule ItemAttachmentRule = EAttachmentRule::KeepRelative;		// Not an AItem
		if (UKismetMathLibrary::ClassIsChildOf(ItemToAdd->GetClass(), AItem::StaticClass())) {
			ItemAttachmentRule = EAttachmentRule::KeepWorld;					// Is an AItem
		}
		// Add the new item
		Item = ItemToAdd;
		Item->AttachToComponent(ItemScene, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, ItemAttachmentRule, ItemAttachmentRule, true));
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

// Activé à la fermeture du tiroir
void ADrawer::OnCloseCPP() {
	TranslationStart = FVector(0.0f, 0.0f, 0.0f);	// Enlève la translation de départ
}

void ADrawer::FurnitureAction(float DeltaTime)
{
	Super::FurnitureAction(DeltaTime);

	// Translation
	TranslationAction(TranslationOrigin + TranslationStart, TranslationEnd, DeltaTime);

}

