// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LogBookManager.generated.h"

UCLASS(BlueprintType, Blueprintable)
class LITM_API ALogBookManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALogBookManager();

	// VARIABLES
public:
	// Debug
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Logbook")
		bool DebugPrintLists = false;
	// Liste des feuilles
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Logbook")
		TArray<class ASheet*> SheetList;
	// Liste des magn�tophones
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Logbook")
		TArray<class ATapeRecorder*> TapeRecorderList;
	// Liste des cl�s
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Logbook")
		TArray<class AKeyObject*> KeyList;
	// Liste d'items (ex : feuilles & magn�tos)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Logbook")
		TArray<class AItem*> ItemList;

protected:
	// Classe du panneau actuel du journal de bord
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		TSubclassOf<UUserWidget> ActualLogbookPanelClass;
	// Liste des feuilles d�couvertes
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		TArray<bool> SheetFoundList;
	// Liste des magn�tophones d�couverts
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		TArray<bool> TapeRecorderFoundList;
	// Liste des cl�s d�couvertes
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		TArray<bool> KeyFoundList;
	// Liste des items d�couverts
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		TArray<bool> ItemFoundList;

	// METHODS
public:
	// Initialisation
	UFUNCTION(BlueprintCallable)
		void Init();
	// Print des valeurs des deux listes
	UFUNCTION(BlueprintCallable)
		void PrintList();
	// Ajoute une pi�ce dans les listes
	UFUNCTION(BlueprintCallable)
		void AddToList(class AInteractible* NewItem);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
