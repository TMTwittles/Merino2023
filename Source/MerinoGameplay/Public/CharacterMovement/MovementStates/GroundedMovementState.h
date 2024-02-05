// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "MerinoMovementState.h"
#include "GroundedMovementState.generated.h"

class ULockOnMovementStateBehaviour;
/**
 * 
 */
UCLASS(BlueprintType)
class MERINOGAMEPLAY_API UGroundedMovementState : public UMerinoMovementState
{
protected:
	virtual void PostConfigure(UMovementStateData* Data) override;

private:
	GENERATED_BODY()

public:
	UGroundedMovementState();
	virtual void Tick(float DeltaTime) override;
	

protected:
	virtual void OnEnter() override;

protected:
	float CalculateNormalizedElapsedDecelerationTime();
	void StickToGround();

protected:
	FVector LastActiveVelocity;
	ULockOnMovementStateBehaviour* LockOnBehaviour;
};
