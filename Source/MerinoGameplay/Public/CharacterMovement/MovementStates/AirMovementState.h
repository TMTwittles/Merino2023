// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterMovement/MovementStateData/AirMovementStateData.h"
#include "CharacterMovement/MovementStates/MerinoMovementState.h"
#include "AirMovementState.generated.h"

/**
 * 
 */
UCLASS()
class MERINOGAMEPLAY_API UAirMovementState : public UMerinoMovementState
{
public:
	virtual void Tick(float DeltaTime) override;

private:
	GENERATED_BODY()

public:
	void OnEnter() override;
	FVector CalculateAirControlVector(FVector AirControlDirection, float DeltaTime);

protected:
	virtual void PostConfigure(UMovementStateData* _Data) override;

private:
	UAirMovementStateData* Data;
	FVector LastActiveAirMovementVector;
	FVector PrevAirMovementVector;
	FVector CurrentAirMovementVector;
};
