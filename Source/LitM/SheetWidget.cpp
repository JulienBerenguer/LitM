// Fill out your copyright notice in the Description page of Project Settings.


#include "SheetWidget.h"
#include "Sheet.h"
#include "Engine/Engine.h"
#include "Engine/Texture2D.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"



// Init widget elements
void USheetWidget::SetOwner(ASheet* NewOwner) {
    if (IsValid(NewOwner)) {
        Owner = NewOwner;
        UE_LOG(LogTemp, Warning, TEXT("SheetWidget.cpp : Owner set"));
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("SheetWidget.cpp : Owner NOT set"));
    }

}


// Init rich text & Texture
void USheetWidget::InitInfosSheetWidget(FSheetWidgetInfos NewInfos) {
    InitSheetWidget(NewInfos.Text, NewInfos.Style, NewInfos.Texture, NewInfos.MatchSize);
}

// Init rich text & Texture
void USheetWidget::InitSheetWidget(FText Text, UDataTable* Style, UTexture2D* Texture, bool MatchSize) {
	SetRichText(CentralText, Text, Style);
	SetImage(Background, Texture, MatchSize);
}

// Set rich text (text & style)
void USheetWidget::SetRichText(URichTextBlock* RichText, FText Text, UDataTable* Style) {
    if (IsValid(RichText)) {
        RichText->SetText(Text);
        RichText->SetTextStyleSet(Style);
        //RebuildWidget();
    }
    else {
        // > Erreur
        UE_LOG(LogTemp, Warning, TEXT("ERROR SheetWidget.cpp : RichText is NULL"));
    }
}

// Set image
void USheetWidget::SetImage(UImage* Image, UTexture2D* Texture, bool MatchSize) {
    if (IsValid(Image)) {
        Image->SetBrushFromTexture(Texture, MatchSize);
        //RebuildWidget();
    }
    else {
        // > Erreur
        UE_LOG(LogTemp, Warning, TEXT("ERROR SheetWidget.cpp : Background is NULL"));
    }
}


// Init widget elements
/*void USheetWidget::InitWidgetElements(UImage* Image, URichTextBlock* RichText) {
    // Set Background Image
    if (IsValid(Image) && IsValid(RichText)) {
        Background = Image;
        CentralText = RichText;
        // Debug
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, Background->GetFName().ToString());
        UE_LOG(LogTemp, Warning, TEXT("Good SheetWidget.cpp : Init elements success"));
    }
    else {
        // > Erreur
        UE_LOG(LogTemp, Warning, TEXT("ERROR SheetWidget.cpp : Init elements failed"));
    }
}*/

/*void USheetWidget::NativeConstruct()
{
    // Do some custom setup

    // Call the Blueprint "Event Construct" node
    Super::NativeConstruct();


    if (IsValid(Owner)) {
        FString ContextString;
        FSheetWidgetText* SheetWidgetTextStruct = Owner->Text.DataTable->FindRow<FSheetWidgetText>(Owner->Text.RowName, ContextString);
        if (SheetWidgetTextStruct != nullptr) {
            // Get widget text from result struct
            FText WidgetText = SheetWidgetTextStruct->WidgetText;

            // Debug
            //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, WidgetText.ToString());

            // All variables gathered => Call init widget
            InitSheetWidget(WidgetText, Owner->Style, Owner->BackgroundTexture, Owner->BackgroundTextureMatchSize);
            //FSheetWidgetInfos Infos;
            //Infos.Text = WidgetText;
            //Infos.Style = Owner->Style;
            //Infos.Texture = Owner->BackgroundTexture;
            //Infos.MatchSize = Owner->BackgroundTextureMatchSize;
            //SaveInfosSheetWidget(Infos);
            UE_LOG(LogTemp, Warning, TEXT("SheetWidget.cpp : NativeConstruct work !"));
        }
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("SheetWidget.cpp : NativeConstruct NOT work !"));
    }

    //UE_LOG(LogTemp, Warning, TEXT("SheetWidget.cpp : NativeConstruct"));
}*/

// https://forums.unrealengine.com/development-discussion/c-gameplay-programming/1383149-can-t-make-c-communicate-with-widget-blueprint
/*bool USheetWidget::Initialize()
{
    bool Success = Super::Initialize();
    if (!Success) return false;

    if (!ensure(Background) || !ensure(CentralText)) { return false; } // check for nullptrs

    // Actions
    //InitInfosSheetWidget(Infos);
    if (IsValid(Owner)) {
        FString ContextString;
        FSheetWidgetText* SheetWidgetTextStruct = Owner->Text.DataTable->FindRow<FSheetWidgetText>(Owner->Text.RowName, ContextString);
        if (SheetWidgetTextStruct != nullptr) {
            // Get widget text from result struct
            FText WidgetText = SheetWidgetTextStruct->WidgetText;

            // Debug
            //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, WidgetText.ToString());

            // All variables gathered => Call init widget
            InitSheetWidget(WidgetText, Owner->Style, Owner->BackgroundTexture, Owner->BackgroundTextureMatchSize);
            FSheetWidgetInfos Infos;
            Infos.Text = WidgetText;
            Infos.Style = Owner->Style;
            Infos.Texture = Owner->BackgroundTexture;
            Infos.MatchSize = Owner->BackgroundTextureMatchSize;
            SaveInfosSheetWidget(Infos);
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("SheetWidget.cpp : Initialize"));
    return true;
}*/


/*void USheetWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    // Make sure to call the base class's NativeTick function
    Super::NativeTick(MyGeometry, InDeltaTime);

    // Do your custom tick stuff here
    // Actions
    //InitInfosSheetWidget(Infos);
    if (IsValid(Owner)) {
        FString ContextString;
        FSheetWidgetText* SheetWidgetTextStruct = Owner->Text.DataTable->FindRow<FSheetWidgetText>(Owner->Text.RowName, ContextString);
        if (SheetWidgetTextStruct != nullptr) {
            // Get widget text from result struct
            FText WidgetText = SheetWidgetTextStruct->WidgetText;

            // Debug
            //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, WidgetText.ToString());

            // All variables gathered => Call init widget
            InitSheetWidget(WidgetText, Owner->Style, Owner->BackgroundTexture, Owner->BackgroundTextureMatchSize);
            //FSheetWidgetInfos Infos;
            //Infos.Text = WidgetText;
            //Infos.Style = Owner->Style;
            //Infos.Texture = Owner->BackgroundTexture;
            //Infos.MatchSize = Owner->BackgroundTextureMatchSize;
            //SaveInfosSheetWidget(Infos);
            UE_LOG(LogTemp, Warning, TEXT("SheetWidget.cpp : Tick"));
        }
    }

}*/

// Save widget infos for later init
/*void USheetWidget::SaveInfosSheetWidget(FSheetWidgetInfos NewInfos) {
    Infos = NewInfos;
    UE_LOG(LogTemp, Warning, TEXT("SheetWidget.cpp : SaveInfos"));
}*/




/*USheetWidget::USheetWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

}


void USheetWidget::NativeConstruct()
{
    // Do some custom setup

    // Call the Blueprint "Event Construct" node
    Super::NativeConstruct();

    //Background = CreateDefaultSubobject<UImage>(TEXT("CentralText"));
    //CentralText = CreateDefaultSubobject<URichTextBlock>(TEXT("CentralText"));
    //Background = ConstructObject<UImage>(UImage::StaticClass());
    //CentralText = ConstructObject<URichTextBlock>(URichTextBlock::StaticClass());


    //Background = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), TEXT("Background"));
    //Background->AddToRoot();
    //CentralText = WidgetTree->ConstructWidget<URichTextBlock>(URichTextBlock::StaticClass(), TEXT("CentralText"));
    //CentralText->AddToRoot();

    RebuildWidget();
}

void USheetWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    // Make sure to call the base class's NativeTick function
    Super::NativeTick(MyGeometry, InDeltaTime);

    // Do your custom tick stuff here
}

TSharedRef<SWidget> USheetWidget::RebuildWidget()
{
    // Créé le RootCanvas
    UPanelWidget* RootWidget = Cast<UPanelWidget>(GetRootWidget());

    if (!RootWidget)
    {
        RootWidget = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), (TEXT("Root")));
        UCanvasPanelSlot* RootWidgetSlot = Cast<UCanvasPanelSlot>(RootWidget->Slot);
        WidgetTree->RootWidget = RootWidget;
    }

    // Appel du RebuildWidget avant override
    TSharedRef<SWidget>    Widget = Super::RebuildWidget();

    // Si Root bien créé => création des éléments
    if (RootWidget && WidgetTree)
    {
        if (!Background && !CentralText)
        {
            Background = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), TEXT("Background"));
            CentralText = WidgetTree->ConstructWidget<URichTextBlock>(URichTextBlock::StaticClass(), TEXT("CentralText"));

            RootWidget->AddChild(Background);
            RootWidget->AddChild(CentralText);

            //UCanvasPanelSlot* BorderSlot = Cast<UCanvasPanelSlot>(BorderWidget->Slot);
            //BorderSlot->SetAutoSize(true);
            //FLinearColor BorderColor(0.0f, 0.0f, 0.0f, 0.5f);
            //BorderWidget->SetBrushColor(BorderColor);
            //FMargin Padding(10.0f, 4.0f, 10.0f, 4.0f);
            //BorderWidget->SetPadding(Padding);


            // Interdit au texte de dépasser la size du RichText
            CentralText->SetAutoWrapText(true);
        }
    }
    return Widget;
}*/


