// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MerinoMathStatics.generated.h"

/**
 * 
 */
UCLASS()
class MERINO23_API UMerinoMathStatics : public UObject
{
	GENERATED_BODY()

	public:
	static float GetUnsignedAngleBetweenTwoVectors(FVector From, FVector To);
	static float GetSignedAngleBetweenTwoVectorsRelativeToAxis(FVector From, FVector To, FVector Axis);
};
