// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MerinoMovementState.h"
#include "JumpingMovementState.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MERINOGAMEPLAY_API UJumpingMovementState : public UMerinoMovementState
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float UpwardsJumpProgressNormalized;
	
protected:
	virtual void OnEnter() override;

private:
	float CalculateUpwardsJumpGravity();
	
	FVector JumpVelocityClamped;
	float JumpGravityLerped;
	float StartingJumpHeight;
	float CurrentJumpDistance;
};
