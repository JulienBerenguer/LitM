// Fill out your copyright notice in the Description page of Project Settings.


#include "Wardrobe.h"
#include "Drawer.h"
#include "Kismet/KismetMathLibrary.h"

AWardrobe::AWardrobe() {
	//Super::AFurniture();

}

// Called when the game starts or when spawned
void AWardrobe::BeginPlay()
{
	Super::BeginPlay();

	// Add the item in one of the drawers
	//AddItem();
}

void AWardrobe::GetAllDrawers() {
	// Init lists
	ChildActorList.Init(nullptr, 0);
	ChildActorDrawerList.Init(nullptr, 0);

	// Get all chid actors and test if it's a drawer
	GetAllChildActors(ChildActorList, true);

	// Remove NULL pointers
	ChildActorList.Remove(nullptr);

	ADrawer* ActualDrawer = nullptr;
	for (AActor* ChildActor : ChildActorList)
	{
		// Child actor test
		ActualDrawer = Cast<ADrawer>(ChildActor);
		// It's a drawer
		if (ActualDrawer != nullptr) {
			// Add to the drawer list
			ChildActorDrawerList.Add(ActualDrawer);
			UE_LOG(LogTemp, Warning, TEXT("Wardrobe.cpp : New drawer found"));
			//UE_LOG(LogTemp, Warning, TEXT("Wardrobe.cpp : New drawer found : '%s'"), *ActualDrawer);
		}
	}
	// Remove NULL pointers
	ChildActorDrawerList.Remove(nullptr);
}

void AWardrobe::AddItemInRandomDrawer(AActor* ItemToAdd) {
	// Item ref valid
	if (IsValid(ItemToAdd)) {
		// Get drawers
		GetAllDrawers();

		UE_LOG(LogTemp, Warning, TEXT("Wardrobe.cpp : Drawer index max : '%d'"), ChildActorDrawerList.Num());

		// Select a random drawer
		int DrawerIndexSelected = UKismetMathLibrary::RandomIntegerInRange(0, ChildActorDrawerList.Num() - 1);

		UE_LOG(LogTemp, Warning, TEXT("Wardrobe.cpp : Drawer index : '%d'"), DrawerIndexSelected);

		// If index is in array
		if (ChildActorDrawerList.IsValidIndex(DrawerIndexSelected)) {
			// Attach the item
			ChildActorDrawerList[DrawerIndexSelected]->AttachActor(ItemToAdd);	// /!\ Prévoir le cas si plusieurs AItem sont sur le même AWardrobe
		}
	}
}

/*void AWardrobe::AddItem() {
	// Item class valid
	if (IsValid(ItemToAdd)) {
		// Get all chid actors and test if it's a drawer
		GetAllChildActors(ChildActorList, true);
		ADrawer* ActualDrawer = nullptr; 
		for (AActor* ChildActor : ChildActorList)
		{
			// Child actor test
			ActualDrawer = Cast<ADrawer>(ChildActor);
			// It's a drawer
			if (ActualDrawer != nullptr) {
				// Add to the drawer list
				ChildActorDrawerList.Add(ActualDrawer);
			}
		}

		// Select a random drawer
		int DrawerIndexSelected = UKismetMathLibrary::RandomIntegerInRange(0, ChildActorDrawerList.Max() - 1);
		
		UE_LOG(LogTemp, Warning, TEXT("Wardrobe.cpp : Drawer index : '%d'"), DrawerIndexSelected);

		// If index is in array
		if (ChildActorDrawerList.IsValidIndex(DrawerIndexSelected)) {
			// Replace the item class
			ChildActorDrawerList[DrawerIndexSelected]->ItemChildActor->SetChildActorClass(ItemToAdd);
			ChildActorDrawerList[DrawerIndexSelected]->ItemChildActor->CreateChildActor();
			// If item class is an interactible
			//if (UKismetMathLibrary::ClassIsChildOf(ItemToAdd, AInteractible::StaticClass())) {
			//	// Replace name and description
			//	Cast<AInteractible>(ChildActorDrawerList[DrawerIndexSelected]->ItemChildActor)->Name = ItemName;
			//	Cast<AInteractible>(ChildActorDrawerList[DrawerIndexSelected]->ItemChildActor)->Description = ItemDescription;
			//}
		}

		//for (AActor* ChildActor : ChildActorList)
		//{
		//	// Child actor test
		//	ActualDrawer = Cast<ADrawer>(ChildActor);
		//	// It's a drawer
		//	if (ActualDrawer != nullptr) {
		//		// Replace the item class
		//		ActualDrawer->ItemChildActor->SetChildActorClass(ItemToAdd);
		//		// If item class is an interactible
		//		if (UKismetMathLibrary::ClassIsChildOf(ItemToAdd, AInteractible::StaticClass())) {
		//			// Replace name and description
		//			Cast<AInteractible>(ActualDrawer->ItemChildActor)->Name = ItemName;
		//			Cast<AInteractible>(ActualDrawer->ItemChildActor)->Description = ItemDescription;
		//		}
		//	}
		//}
	}
}*/