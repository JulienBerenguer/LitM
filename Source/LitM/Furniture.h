// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactible.h"
#include "SoundManager.h"
#include "Furniture.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EActionType : uint8
{
	Translation	UMETA(DisplayName = "Translation"),
	Rotation	UMETA(DisplayName = "Rotation"),
};

UENUM(BlueprintType)
enum class EFurnitureEventType : uint8
{
	Lock		UMETA(DisplayName = "Lock"),
	Unlock		UMETA(DisplayName = "Unlock"),
	PostUnlock	UMETA(DisplayName = "PostUnlock"),
	Open		UMETA(DisplayName = "Open"),
	Close		UMETA(DisplayName = "Close"),
};

UCLASS()
class LITM_API AFurniture : public AInteractible
{
	GENERATED_BODY()
public:
	AFurniture();

	// VARIABLES meta = (AllowedClasses = "AItem, ASheet")
public:
	// Référence de la clé si verrouillé (si non-verrouillé, alors ne pas mettre de clé)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - General")
		class AKeyObject* KeyRef = nullptr;
	// Active / Désactive les events
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - General")
		bool EnableFurnitureEvents = true;
	// Temps de l'action d'interaction (en secondes)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - General", meta = (UIMin = 0.001f))
		float Speed = 1.0f;
	// Son de l'audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Sound")
		float AudioVolumeMultiplier = 1.0f;
protected:
	// Est verrouillé (à true si une clé y est assignée)
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Object Options - Private")
		bool IsLocked = false;
	// Rotation / Translation : Valeur d'origine => cas hors 0 non-gérés => reste en privé
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Object Options - Private")
		float ValueBeginning = 0.0f;
	// Rotation / Translation : Valeur actuelle
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Object Options - Private")
		float ValueActual = 0.0f;
	// Objet en cours d'utilisation
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Object Options - Private")
		bool IsUsed = false;
	// Empêche l'utilisation si mis sur False
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Object Options - Private")
		bool IsInteractible = true;
	// Sens d'ouverture : true = s'ouvre | false = se ferme
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Object Options - Private")
		bool OpeningDirection = true;
	// Identifiant de la clé associée
	uint32 KeyID;
	// Alpha du Lerp
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Object Options - Private")
		float Alpha = 0.0f;

	// Gestion des sons d'event (ouverture, fermeture, objet verrouillé, ...)
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Object Options - Private")
		USoundManager* Sound;

	// COMPONENTS
public:
	// Mesh
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		class UStaticMeshComponent* ObjectMesh;
	// Rotation Point
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		class USceneComponent* RotationScene;

	// METHODS
public:
	// Init
	UFUNCTION(BlueprintCallable, Category = "Object Functions")
		void Init();

	// Action à effectuer => à modifier dans les classes filles
	virtual void FurnitureAction(float DeltaTime);

	// Events appelés lors des actions
	UFUNCTION(BlueprintCallable, Category = "Object Functions")
		void CallFurnitureEvent(EFurnitureEventType EventType);
	UFUNCTION(BlueprintImplementableEvent, Category = "Object Functions")
		void OnLock();
	UFUNCTION(BlueprintImplementableEvent, Category = "Object Functions")
		void OnUnlock();
	UFUNCTION(BlueprintImplementableEvent, Category = "Object Functions")
		void OnPostUnlock();
	UFUNCTION(BlueprintImplementableEvent, Category = "Object Functions")
		void OnOpen();
	UFUNCTION(BlueprintImplementableEvent, Category = "Object Functions")
		void OnClose();

	// Fonctions appelés lors des actions
	//UFUNCTION(BlueprintCallable, Category = "Object Functions")
		virtual void OnCloseCPP();

	// A lier dans OnUnlock() pour appeler OnOpen() lorsqu'on veut utiliser le 'USoundManager* Sound' en deux temps
	UFUNCTION(BlueprintCallable, Category = "Object Functions")
		void SoundUnlockToOpen();
	UFUNCTION(BlueprintCallable, Category = "Object Functions")
		void EventSoundOnFinished();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Vérifie que l'objet a une clé enregistrée (cas où la clef est en child_actor)
	bool HasKey();

	// FurnitureAction() actions
	bool CanDoAction();
	void TranslationAction(FVector Origin, FVector End, float DeltaTime);
	void RotationAction(FRotator Origin, FRotator End, float DeltaTime);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Override de la fonction d'interaction
	virtual void OnInteraction() override;

};
