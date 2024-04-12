// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HSFM/States/MerinoState.h"
#include "MovementState.generated.h"

class UMerinoMovementComponent;

/**
 * 
 */
UCLASS(Abstract)
class MERINOGAMEPLAY_API UMovementState : public UMerinoState
{
	GENERATED_BODY()

public:
	virtual void EnterState();

protected:
	virtual void PostInitialise(AActor* InOwner, UMerinoStateProperties* InStateProperties);
	
protected:
	UPROPERTY()
	float Acceleration;

	UPROPERTY()
	float Deceleration;

	UPROPERTY()
	float AngularAcceleration;

	UPROPERTY()
	float MaxSpeed;

	UPROPERTY()
	float Gravity;

	UPROPERTY()
	float MaxFallingSpeed;

	UPROPERTY()
	float MinimumJumpAnglePercentage;

	UPROPERTY()
	TObjectPtr<UMerinoMovementComponent> MovementComponent;
};
