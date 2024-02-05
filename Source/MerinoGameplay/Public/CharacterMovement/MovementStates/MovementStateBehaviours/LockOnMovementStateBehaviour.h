// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterMovement/MovementStates/MovementStateBehaviours/MovementStateBehaviour.h"
#include "LockOnMovementStateBehaviour.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MERINOGAMEPLAY_API ULockOnMovementStateBehaviour : public UMovementStateBehaviour
{
private:
	GENERATED_BODY()
	
public:
	virtual void TickBehaviour(float DeltaTime) override;
	FVector GetLockOnDirection();
	FVector CalculateDirectionRelativeToLockOn(FVector InputDirection);
	
protected:
	virtual void OnActive() override;
	virtual void OnInActive() override;

private:
	FVector LockOnDirection;
};
