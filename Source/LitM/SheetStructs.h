// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "SheetStructs.generated.h"

/**
 * 
 */


USTRUCT(BlueprintType, Blueprintable)
struct LITM_API FSheetWidgetText : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	// List of tic tact toe boxes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true))
		FText WidgetText;

	/*// Victory check - Check if all conditions are met
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<bool> VictoryList;*/
};

USTRUCT(BlueprintType, Blueprintable)
struct LITM_API FSheetWidgetInfos
{
	GENERATED_USTRUCT_BODY()

	// RichText text
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Text;
	// RichText style
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UDataTable* Style;
	// Image texture
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Texture;
	// Image if texture needed to match size
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool MatchSize;
};


class LITM_API SheetStructs
{
public:
	SheetStructs();
	~SheetStructs();
};
