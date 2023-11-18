// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovementStateData.h"
#include "JumpingMovementStateData.generated.h"

/**
 * 
 */
UCLASS()
class MERINOGAMEPLAY_API UJumpingMovementStateData : public UMovementStateData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float MaxDistanceFromPeakJumpHeight;
	UPROPERTY(EditAnywhere)
	float MaxJumpHeight;
	UPROPERTY(EditAnywhere)
	float AirControl;
};
