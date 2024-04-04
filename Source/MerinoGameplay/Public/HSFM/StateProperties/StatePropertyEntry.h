// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "StatePropertyType.h"
#include "HSFM/MerinoStateID.h"
#include "StatePropertyEntry.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct MERINOGAMEPLAY_API FStatePropertyEntry : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PropertyKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EStatePropertyType> PropertyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PropertyValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAffectsAllStates = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TEnumAsByte<EMerinoStateID>> SharedStates;
};
