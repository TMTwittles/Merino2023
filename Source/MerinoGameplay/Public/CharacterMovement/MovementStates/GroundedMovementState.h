﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MerinoMovementState.h"
#include "GroundedMovementState.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MERINOGAMEPLAY_API UGroundedMovementState : public UMerinoMovementState
{
	GENERATED_BODY()

public:
	UGroundedMovementState();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnEnter() override;

private:
	float CalculateNormalizedElapsedDecelerationTime();
	
	FVector LastActiveVelocity;
};