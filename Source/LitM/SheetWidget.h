// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SheetStructs.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/RichTextBlock.h"
#include "SheetWidget.generated.h"

/**
 * 
 */
UCLASS()
class LITM_API USheetWidget : public UUserWidget
{
	GENERATED_BODY()

	// VARIABLES
protected:
	// Infos du widget
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Options - SheetWidget")
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		FSheetWidgetInfos Infos;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Private")
		class ASheet* Owner;

	// COMPONENTS
public:
	// Image de fond
	UPROPERTY(meta = (BindWidget))
		UImage* Background;

	// Texte
	UPROPERTY(meta = (BindWidget))
		URichTextBlock* CentralText;

	// METHODS
public:

	// Init widget elements
	UFUNCTION(BlueprintCallable)
		void SetOwner(class ASheet* NewOwner);

	// Init rich text & Texture
	UFUNCTION(BlueprintCallable)
		void InitInfosSheetWidget(FSheetWidgetInfos NewInfos);

	// Init rich text & Texture
	UFUNCTION(BlueprintCallable)
		void InitSheetWidget(FText Text, UDataTable* Style, UTexture2D* Texture, bool MatchSize);

	// Set rich text (text & style)
	UFUNCTION(BlueprintCallable)
		void SetRichText(URichTextBlock* RichText, FText Text, UDataTable* Style);

	// Set image
	UFUNCTION(BlueprintCallable)
		void SetImage(UImage* Image, UTexture2D* Texture, bool MatchSize);


	UFUNCTION(BlueprintImplementableEvent, Category = "Object Functions")
		void OnOpen();
	UFUNCTION(BlueprintImplementableEvent, Category = "Object Functions")
		void OnClose();



	/*// Sets default values for this actor's properties
	//USheetWidget();
	USheetWidget(const FObjectInitializer& ObjectInitializer);

	// Optionally override the Blueprint "Event Construct" event
	virtual void NativeConstruct() override;

	// Optionally override the tick event
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual TSharedRef<SWidget> RebuildWidget() override;*/


	// Optionally override the Blueprint "Event Construct" event
	//virtual void NativeConstruct() override;


	// Optionally override the tick event
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// Optionally override the Blueprint "Event OnInitialized" event
	//virtual void Construct() override;

	// Optionally override the Blueprint "Event OnInitialized" event
	//virtual bool Initialize() override;

	// Appel en blueprint pour le Init widget elements
	//UFUNCTION(BlueprintImplementableEvent, Category = "Object Functions")
		//void InitCall();

	// Init widget elements
	//UFUNCTION(BlueprintCallable)
		//void InitWidgetElements(UImage* Image, URichTextBlock* RichText);

	// Save widget infos for later init
	//UFUNCTION(BlueprintCallable)
		//void SaveInfosSheetWidget(FSheetWidgetInfos NewInfos);

};
