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
	UFUNCTION(BlueprintCallable)
	float CalculateInitialVelocityZ() const;
	UFUNCTION(BlueprintCallable)
	float CalculateGravity() const;
public:
	UPROPERTY(EditAnywhere)
	float MaxJumpHeight;
	UPROPERTY(EditAnywhere)
	float TimeReachMaxJumpHeightSeconds;
	UPROPERTY(EditAnywhere)
	float AirControl;
};
