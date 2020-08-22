// Fill out your copyright notice in the Description page of Project Settings.


#include "Furniture.h"
#include "KeyObject.h"
#include "LitMCharacter.h"
#include "Components/AudioComponent.h"

AFurniture::AFurniture()
{
	// Meshs
	RotationScene = CreateDefaultSubobject<USceneComponent>(TEXT("RotationScene"));
	RootComponent = RotationScene;
	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectMesh"));
	ObjectMesh->AttachTo(RotationScene);

	// Variables
	ValueActual = ValueBeginning;
}

// Called when the game starts or when spawned
void AFurniture::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void AFurniture::Init(){
	// Si la porte a une cl� associ�e => verouill�e
	HasKey();

	// Initialisation du Sound Manager => /!\ Doit �tre dans le BeginPlay pour fonctionner et non dans le constructeur
	Sound = NewObject<USoundManager>(this, TEXT("Sound"));
	Sound->VolumeMultiplier = AudioVolumeMultiplier;
}

// Permet d'appeler un event dans le blueprint
void AFurniture::CallFurnitureEvent(EFurnitureEventType EventType) {
	if (EnableFurnitureEvents) {
		switch (EventType)
		{
		case EFurnitureEventType::Lock:
			OnLock();
			break;
		case EFurnitureEventType::Unlock:
			OnUnlock();
			break;
		case EFurnitureEventType::PostUnlock:
			OnPostUnlock();
			break;
		case EFurnitureEventType::Open:
			OnOpen();
			break;
		case EFurnitureEventType::Close:
			OnClose();
			OnCloseCPP();	// Pour enlever la valeur de d�part
			break;
		default:
			//
			break;
		}
	}
}

// V�rifie que l'objet a une cl� enregistr�e (cas o� la clef est en child_actor)
bool AFurniture::HasKey() {

	// Variables locales => flag et cl� � la bonne classe
	bool ValidKey = false;
	AKeyObject* KeyObject = nullptr;
	TArray<AActor*> ChildActorList;

	// Objet r�f�renc�
	if (KeyRef != nullptr) {

		// Teste voir si l'objet fourni est directement une cl�
		KeyObject = Cast<AKeyObject>(KeyRef);
		if (KeyObject != nullptr) ValidKey = true;	// AKeyObject actor

		// Teste voir si l'objet fourni est indirectement une cl�
		else {
			KeyRef->GetAllChildActors(ChildActorList, true);
			for (AActor* ChildActor : ChildActorList)	
			{
				//UE_LOG(LogTemp, Warning, TEXT("> Child_actor : %s"), *GetNameSafe(ChildActor));
				KeyObject = Cast<AKeyObject>(ChildActor);
				if (KeyObject != nullptr) ValidKey = true;	// AKeyObject child actor
			}
		}

	}
	//UE_LOG(LogTemp, Warning, TEXT("> %s : %d"), *GetNameSafe(this), ValidKey);

	// Cl� valide
	if (ValidKey) {
		IsLocked = true;
		KeyID = KeyObject->GetUniqueID();
		return true;
	}
	// Pas de cl� valide trouv�e
	else return false;
}


//---- Interaction ----

// Lors de l'action
void AFurniture::OnInteraction()
{
	Super::OnInteraction();

	UE_LOG(LogTemp, Warning, TEXT("INTERACTION"));
	
	
	// Si d�j� d�verrouill�
	if (!IsLocked) {
		// Une seule fois, n'y passe plus tant que l'action n'est pas finie
		if (!IsUsed) {
			if (OpeningDirection) {
				if (EnableFurnitureEvents) OnOpen();	// Meuble qui s'ouvre
			}
			else {
				if (EnableFurnitureEvents) {			// Meuble qui se ferme
					OnClose();	
					OnCloseCPP();	// Pour enlever la valeur de d�part
				}
			}
		}
		IsUsed = true;
	}
	// Si verrouill�
	else {
		// Si le joueur a la cl� n�cessaire
		if (Cast<ALitMCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn())->HasKey(KeyID)) {
			// Une seule fois, n'y passe plus tant que l'action n'est pas finie
			if (!IsUsed && EnableFurnitureEvents) OnUnlock();	// Meuble qui s'ouvre et qui vient d'�tre d�verrouill�e
			IsLocked = false;
			IsUsed = true;
			if (EnableFurnitureEvents) OnPostUnlock();	// Apr�s un event d'Unlock (prendre en compte le changement de variables)
		}
		else {
			if (EnableFurnitureEvents) OnLock();		// Meuble qui ne s'ouvre pas et reste verrouill�
		}
	}

}

// Appel� � la fin du son par SoundUnlockToOpen()
void AFurniture::EventSoundOnFinished() {
	// Debug
	UE_LOG(LogTemp, Warning, TEXT("> SoundOnFinished"));
	// Autorise de nouveau l'utilisation de l'objet
	IsInteractible = true;
	// Pr�cise que le joueur n'utilise pas l'objet pour pouvoir d�clencher l'event OnOpen() / OnClose() et ne pas tomber dans la restriction contre les events multiples
	IsUsed = false;
	// Effectue la seconde action automatiquement => OnOpen() / OnClose()
	OnInteraction();


}

// A utiliser apr�s e son dans le OnUnlock()
void AFurniture::SoundUnlockToOpen() {
	// Interdit d'utiliser l'objet tant que l'action en deux temps n'est pas termin�e
	IsInteractible = false;
	// Bind OnAudioFinished USoundManager event to EventSoundOnFinished() local function
	Sound->Audio->OnAudioFinished.AddDynamic(this, &AFurniture::EventSoundOnFinished);
}

// Called every frame
void AFurniture::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Action en Tick lors d'une interaction => OnInteraction()
	FurnitureAction(DeltaTime);
}

// Tick activ� lors de l'action
void AFurniture::FurnitureAction(float DeltaTime)
{
	// A modifier dans les fonctions filles
}

// Lors de la fermeture au niveau du CPP
void AFurniture::OnCloseCPP()
{
	// A modifier dans les fonctions filles
}


// ---- Functions in FurnitureAction() ----

// R�unit les conditions
bool AFurniture::CanDoAction() {
	// Peut �tre utilis�
	if (IsInteractible) {
		// Si d�verrouill�
		if (!IsLocked) {
			// Si objet utilis�
			if (IsUsed) {
				// Peut effectuer l'action
				return true;
			}
		}
	}
	// Ne peut pas effectuer l'action
	return false;
}

// Translation en Tick
void AFurniture::TranslationAction(FVector Origin, FVector End, float DeltaTime){
	// Si peut effectuer l'action
	if (CanDoAction()) {

		// Vecteur de translation
		FVector VectorA = FVector(0.0f, 0.0f, 0.0f);
		FVector VectorB = FVector(0.0f, 0.0f, 0.0f);

		// S'ouvre
		if (OpeningDirection) {
			VectorA = Origin;
			VectorB = End;
		}
		// Se ferme
		else {
			VectorA = End;
			VectorB = Origin;
		}

		// Alpha du Lerp => action en secondes
		Alpha += (1 / Speed) * DeltaTime;

		// Lerp
		FVector NewTranslation = FMath::LerpStable(VectorA, VectorB, Alpha);

		// Effectue la translation (en tenant compte de la position d'origine)
		ObjectMesh->SetRelativeLocation(NewTranslation);

		// Si la translation est termin�e => arr�te l'action et change de sens
		if (Alpha >= 1.0f) {
			IsUsed = false;
			OpeningDirection = !OpeningDirection;
			Alpha = 0.0f;
		}
		
	}
}

// Rotation en Tick
void AFurniture::RotationAction(FRotator Origin, FRotator End, float DeltaTime){
	// Si peut effectuer l'action
	if (CanDoAction()) {

		// Rotators
		FRotator RotatorA = FRotator(0.0f, 0.0f, 0.0f);
		FRotator RotatorB = FRotator(0.0f, 0.0f, 0.0f);

		// S'ouvre
		if (OpeningDirection) {
			RotatorA = Origin;
			RotatorB = End;
		}
		// Se ferme
		else {
			RotatorA = End;
			RotatorB = Origin;
		}

		// Alpha du Lerp => action en secondes
		Alpha += (1 / Speed) * DeltaTime;

		// Lerp
		FRotator AngleActual = FMath::LerpRange(RotatorA, RotatorB, Alpha);

		// Effectue la rotation
		ObjectMesh->SetRelativeRotation(AngleActual);


		// Si la rotation est termin�e => arr�te l'action et change de sens
		if (Alpha >= 1.0f) {
			IsUsed = false;
			OpeningDirection = !OpeningDirection;
			Alpha = 0.0f;
		}
		
	}
}