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
	UFUNCTION(BlueprintCallable)
	static float GetUnsignedAngleBetweenTwoVectors(FVector From, FVector To);
	UFUNCTION(BlueprintCallable)
	static float GetSignedAngleBetweenTwoVectorsRelativeToAxis(FVector From, FVector To, FVector Axis);
	static float GetYawFromQuat(FQuat Quat);
	static float GetPitchFromQuat(FQuat Quat);
	static FQuat BuildQuatEuler(float Yaw, float Pitch, float Roll);
	static FVector CalculateCentroid(FVector P1, FVector P2, FVector P3);
};
