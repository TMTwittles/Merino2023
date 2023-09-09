// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PositionGenConfig.generated.h"

class UPositionData;

USTRUCT(BlueprintType)
struct MERINO23_API FPositionGenConfig
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere)
	float PointDistanceApart;
	
	UPROPERTY(EditAnywhere)
	UPositionData* Data;
};
