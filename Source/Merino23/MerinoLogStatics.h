// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MerinoLogStatics.generated.h"

/**
 * 
 */
UCLASS()
class MERINO23_API UMerinoLogStatics : public UObject
{
	GENERATED_BODY()

public:
	static void LogVector(FString LogIdentifier, FVector VectorToLog);
	static void LogFloat(FString LogIdentifier, float FloatToLog);
};
