// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "LitMCharacter.h"
#include "LitMProjectile.h"
#include "Animation/AnimInstance.h"
#include "Interactible.h"
#include "Sheet.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId
#include "Blueprint/WidgetBlueprintLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ALitMCharacter

ALitMCharacter::ALitMCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));


	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);





	// Uncomment the following line to turn motion controllers on by default:
	//bUsingMotionControllers = true;
}

void ALitMCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Mode Menu vers Mode Jeu
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(UGameplayStatics::GetPlayerController(GetWorld(), 0));


	// Initialisation du Puzzle Manager
	int NbPuzzleManagerFind = 0;
	for (TObjectIterator<APuzzleManager> Itr; Itr; ++Itr)
	{
		if (Itr->IsA(APuzzleManager::StaticClass()))
		{
			UE_LOG(LogTemp, Warning, TEXT("LitMCharacter.cpp : PuzzleManager found : '%s'"), *Itr->GetName());
			Puzzle = *Itr;
			NbPuzzleManagerFind++;
		}
	}

	if (NbPuzzleManagerFind == 0) UE_LOG(LogTemp, Warning, TEXT("LitMCharacter.cpp : No PuzzleManager found"));
	if (NbPuzzleManagerFind > 1) UE_LOG(LogTemp, Warning, TEXT("LitMCharacter.cpp : Multiple PuzzleManager found, total : %d"), NbPuzzleManagerFind);

	/*// Initialisation du Logbook Manager
	int NbLogbookManagerFind = 0;
	for (TObjectIterator<ALogBookManager> Itr; Itr; ++Itr)
	{
		if (Itr->IsA(ALogBookManager::StaticClass()))
		{
			UE_LOG(LogTemp, Warning, TEXT("LitMCharacter.cpp : LogbookManager found : '%s'"), *Itr->GetName());
			LogBook = *Itr;
			NbLogbookManagerFind++;
		}
	}

	if (NbLogbookManagerFind == 0) UE_LOG(LogTemp, Warning, TEXT("LitMCharacter.cpp : No LogbookManager found"));
	if (NbLogbookManagerFind > 1) UE_LOG(LogTemp, Warning, TEXT("LitMCharacter.cpp : Multiple LogbookManager found, total : %d"), NbLogbookManagerFind);*/
}

//////////////////////////////////////////////////////////////////////////
// Input

void ALitMCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//Interact
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &ALitMCharacter::Interact);

	// Open puzzle widget
	PlayerInputComponent->BindAction("OpenPuzzle", IE_Released, this, &ALitMCharacter::OpenPuzzle);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ALitMCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALitMCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ALitMCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ALitMCharacter::LookUpAtRate);
}

void ALitMCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ALitMCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ALitMCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ALitMCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ALitMCharacter::Interact_Implementation() 
{

}

// Ajoute une clé dans l'inventaire
void ALitMCharacter::AddKey(uint32 KeyID) {
	KeyArray.Add(KeyID);
}

// Cherche si le joueur a la bonne clé dans son inventaire
bool ALitMCharacter::HasKey(uint32 KeyID) {

	bool ValidKey = false;

	// Cherche si le joueur a la bonne clé dans son inventaire
	for (int i = 0; i < KeyArray.Num(); i++)
	{
		if (KeyID == KeyArray[i]) {
			ValidKey = true;
		}
	}

	return ValidKey;
}



void ALitMCharacter::OpenPuzzle_Implementation()
{
	/*// Puzzle valide
	if (IsValid(Puzzle)) {
		// Affiche / cache le puzzle
		Puzzle->ShowHidePuzzle();
	}*/
}
/*void ALitMCharacter::OpenPuzzle() {

	// Puzzle valide
	if (IsValid(Puzzle)) {

		Puzzle->ShowPuzzle();

	}
}*/

// Ouvre une feuille de carnet de notes
bool ALitMCharacter::OpenSheet(ASheet* NewSheet) {

	// New sheet valid & class valid
	if (IsValid(NewSheet)) {

		// Another sheet
		if (IsValid(Sheet)) {
			// Empty it
			CloseSheet();
		}
		// Sheet empty => add the selected sheet
		//Sheet = CreateWidget<USheetWidget>(GetWorld(), NewSheet->GetSheetWidget(true)->GetClass());
		Sheet = NewSheet->GetSheetWidget(true);

		// It worked, add it to viewport
		if (IsValid(Sheet)) {
			Sheet->AddToViewport();

			// Event d'ouverture de feuille
			Sheet->OnOpen();
		}

		return true;
	}
	return false;
}

// Ferme une feuille de carnet de notes
bool ALitMCharacter::CloseSheet() {

	// If Sheet is valid
	if (IsValid(Sheet)) {

		// Event de fermeture de feuille
		Sheet->OnClose();

		// Then detroy sheet
		Sheet->RemoveFromParent();
		Sheet = nullptr;

		return true;
	}
	return false;
}
