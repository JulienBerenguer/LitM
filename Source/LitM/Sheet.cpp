// Fill out your copyright notice in the Description page of Project Settings.


#include "Sheet.h"
#include "SheetWidget.h"
#include "LitMCharacter.h"
#include "PuzzleManager.h"
#include "UObject/UObjectIterator.h"
#include "Engine/Engine.h"

ASheet::ASheet() {
	// RootScene
	//RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	// Widget
	Widget = CreateDefaultSubobject<UWidgetComponent>(FName("Widget"));
	Widget->AttachTo(RootScene);	
	// Collider
	Collider = CreateDefaultSubobject<UBoxComponent>(FName("Collider"));
	Collider->AttachTo(RootScene);
	// Block all dynamics => for OnInteraction()
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//Block All!
	Collider->BodyInstance.SetResponseToAllChannels(ECR_Block);
}

// Called when the game starts or when spawned
void ASheet::BeginPlay()
{
	Super::BeginPlay();

	InitSheet();
}

// Called every frame
void ASheet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (!IsInit) {
		InitSheet();
	}*/
	//InitSheet();
}


bool ASheet::InitSheet() {
	// The WidgetClass exist ?
	if (IsValid(WidgetClass)) {
		// Create SheetWidget
		SceneSheetWidget = CreateWidget<USheetWidget>(GetWorld(), WidgetClass);
		ShowSheetWidget = CreateWidget<USheetWidget>(GetWorld(), WidgetClass);

		// Init the text, style & background texture of SheetWidget
		if (IsValid(SceneSheetWidget) && IsValid(ShowSheetWidget)) {

			// Call blueprint event to init widget elements
			//Sheet->InitCall();
			SceneSheetWidget->SetOwner(this); 
			ShowSheetWidget->SetOwner(this);
			UE_LOG(LogTemp, Warning, TEXT("Sheet.cpp : SetOwner"));

			// Add UUserWidget to UWidgetComponent (scene only)
			Widget->SetWidget(SceneSheetWidget);

			if (!Text.IsNull() && IsValid(Style) && IsValid(BackgroundTexture)) {

				// Get struct of data table at the correct row
				FString ContextString;
				FSheetWidgetText* SheetWidgetTextStruct = Text.DataTable->FindRow<FSheetWidgetText>(Text.RowName, ContextString);
				if (SheetWidgetTextStruct != nullptr) {
					// Get widget text from result struct
					FText WidgetText = SheetWidgetTextStruct->WidgetText;

					// Debug
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, WidgetText.ToString());

					// All variables gathered => Call init widget
					Widget->SetWidget(ShowSheetWidget);	// Only needed to init widget, but doesn't want show in scene
					ShowSheetWidget->InitSheetWidget(WidgetText, Style, BackgroundTexture, BackgroundTextureMatchSize);


					// All variables gathered => Call init widget => check if we show text on scene
					Widget->SetWidget(SceneSheetWidget);	// => Will be in scene, need to be after SetWidget(ShowSheetWidget);
					if (HideTextOnScene) {
						FText EmptyWidgetText = FText::GetEmpty();	// Hide text ? => Show no text at all
						SceneSheetWidget->InitSheetWidget(EmptyWidgetText, Style, BackgroundTexture, BackgroundTextureMatchSize);
					}
					else SceneSheetWidget->InitSheetWidget(WidgetText, Style, BackgroundTexture, BackgroundTextureMatchSize);



					// Success
					return true;
				}
				else {
					// > Erreur
					UE_LOG(LogTemp, Warning, TEXT("ERROR Sheet.cpp : Text DataTable don't use FSheetWidgetText"));
				}
			}
			else {
				// > Erreur
				UE_LOG(LogTemp, Warning, TEXT("ERROR Sheet.cpp : Variables not valid"));
			}
		}
		else {
			// > Erreur
			UE_LOG(LogTemp, Warning, TEXT("ERROR Sheet.cpp : Sheet not found"));
		}
	}
	else {
		// > Erreur
		UE_LOG(LogTemp, Warning, TEXT("ERROR Sheet.cpp : WidgetClass not found"));
	}
	// Failed
	return false;
}


// Initialise le puzzle si est une pièce de puzzle
void ASheet::InitPuzzle(class APuzzleManager* NewPuzzle) {
	if (IsValid(NewPuzzle)) Puzzle = NewPuzzle;
}

void ASheet::OnInteraction()
{
	Super::OnInteraction();

	/*// Get struct of data table at the correct row
	FString ContextString;
	FSheetWidgetText* SheetWidgetTextStruct = Text.DataTable->FindRow<FSheetWidgetText>(Text.RowName, ContextString);
	if (SheetWidgetTextStruct != nullptr) {
		FText WidgetText = SheetWidgetTextStruct->WidgetText;
		Sheet->InitSheetWidget(WidgetText, Style, BackgroundTexture, BackgroundTextureMatchSize);
	}
	else {
		// > Erreur
		UE_LOG(LogTemp, Warning, TEXT("god damnit"));
	}*/

	
	// Get player
	//APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//ALitMCharacter* CharacterPawn = Cast<ALitMCharacter>(PlayerPawn);

	// Get player => can be in menu and have another pawn possessed
	ALitMCharacter* CharacterPawn = nullptr;
	int NbCharacterFind = 0;
	for (TObjectIterator<ALitMCharacter> Itr; Itr; ++Itr)
	{
		if (Itr->IsA(ALitMCharacter::StaticClass()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Sheet.cpp : LitMCharacter found : '%s'"), *Itr->GetName());
			CharacterPawn = *Itr;
			NbCharacterFind++;
		}
	}

	if (NbCharacterFind == 0) UE_LOG(LogTemp, Warning, TEXT("Sheet.cpp : No LitMCharacter found"));
	if (NbCharacterFind > 1) UE_LOG(LogTemp, Warning, TEXT("Sheet.cpp : Multiple LitMCharacter found, total : %d"), NbCharacterFind);

	// If cast worked
	if (IsValid(CharacterPawn)) {

		// Has already a sheet opened => close it
		if (IsValid(CharacterPawn->Sheet)) {
			CharacterPawn->CloseSheet();
		}
		// Don't have a sheet opened => open it (show)
		else {
			// Only if can be used
			if (CanBeUsed)
			{
				// > Is a puzzle piece
				if (IsValid(Puzzle)) {
					// Add a piece to the puzzle
					Puzzle->FoundPuzzlePiece(this);
					// Open event (show)
					if (ShowSheetWidget != nullptr) ShowSheetWidget->OnOpen();

					// "Destroy" the item (invisible and can't interact with it)
					DestroyIt(DestroyIfUsed);
				}

				// > Is a sheet, not a puzzle piece
				else {
					if (ShowSheetWidget != nullptr) CharacterPawn->OpenSheet(this);
					// "Destroy" the item (invisible and can't interact with it)
					DestroyIt(DestroyIfUsed);
				}
			}
		}
	}
	else {
		// > Erreur
		UE_LOG(LogTemp, Warning, TEXT("ERROR Sheet.cpp : Character not found"));
	}
	
}

/*void ASheet::DestroySheet(bool NewDestroyIfUsed) {
	// "Destroy" the item (invisible and can't interact with it)
	if (NewDestroyIfUsed) {
		RootScene->SetVisibility(false, true);
		CanBeUsed = false;
	}
}*/

void ASheet::DestroyIt(bool NewDestroyIfUsed) {
	// "Destroy" the item (invisible and can't interact with it)
	if (NewDestroyIfUsed) {
		OnDestroy();	// Blueprint Event
		RootScene->SetVisibility(false, true);
		CanBeUsed = false;
	}
}


USheetWidget* ASheet::GetSheetWidget(bool Type) {
	if (Type == true) return ShowSheetWidget;
	else return SceneSheetWidget;
}