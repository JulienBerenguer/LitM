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
	// Liste des magnétophones
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Logbook")
		TArray<class ATapeRecorder*> TapeRecorderList;
	// Liste des clés
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Logbook")
		TArray<class AKeyObject*> KeyList;
	// Liste d'items (ex : feuilles & magnétos)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - Logbook")
		TArray<class AItem*> ItemList;

protected:
	// Classe du panneau actuel du journal de bord
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		TSubclassOf<UUserWidget> ActualLogbookPanelClass;
	// Liste des feuilles découvertes
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		TArray<bool> SheetFoundList;
	// Liste des magnétophones découverts
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		TArray<bool> TapeRecorderFoundList;
	// Liste des clés découvertes
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		TArray<bool> KeyFoundList;
	// Liste des items découverts
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
	// Ajoute une pièce dans les listes
	UFUNCTION(BlueprintCallable)
		void AddToList(class AInteractible* NewItem);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
