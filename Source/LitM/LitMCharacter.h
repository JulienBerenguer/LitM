// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KeyObject.h"
#include "SheetWidget.h"
#include "PuzzleManager.h"
//#include "LogBookManager.h"
#include "LitMCharacter.generated.h"


class UInputComponent;

UCLASS(config=Game)
class ALitMCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;



	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;



	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	/** Motion controller (right hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* R_MotionController;

	/** Motion controller (left hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* L_MotionController;

public:
	ALitMCharacter();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
		void Interact();

	// Ouvre le widget du puzzle
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
		void OpenPuzzle();

	// Ajoute une clé dans l'inventaire
	void AddKey(uint32 KeyID);

	// Cherche si le joueur a la bonne clé dans son inventaire
	bool HasKey(uint32 KeyID);


	// Ouvre une feuille de carnet de notes
	UFUNCTION(BlueprintCallable, Category = "Interaction")
		bool OpenSheet(class ASheet* NewSheet);

	// Ferme une feuille de carnet de notes
	UFUNCTION(BlueprintCallable, Category = "Interaction")
		bool CloseSheet();


protected:
	// Liste de clés dans l'inventaire du joueur
	TArray<uint32> KeyArray;

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ALitMProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint32 bUsingMotionControllers : 1;

	// Liste des pièces de puzzle ( /!\ l'ordre compte /!\ )
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Manager - Puzzle")
		//TArray<class ASheet*> PuzzlePiecesList;

	// Gestionnaire de puzzle
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		APuzzleManager* Puzzle;

	// Feuille de carnet de notes => si différent de NULL, alors en a une d'ouvert
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		USheetWidget* Sheet;

	/*// Gestionnaire du journal de bord
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		ALogBookManager* LogBook;*/



protected:
	
	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	//bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
//	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

