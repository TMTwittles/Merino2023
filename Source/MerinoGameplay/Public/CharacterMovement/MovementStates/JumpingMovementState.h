// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "MerinoMovementState.h"
#include "JumpingMovementState.generated.h"

class UJumpingMovementStateData;
/**
 * 
 */
UCLASS(BlueprintType)
class MERINOGAMEPLAY_API UJumpingMovementState : public UMerinoMovementState
{
private:
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnEnter() override;
	virtual void PostConfigure(UMovementStateData* _Data) override;
private:
	void TickJump(float DeltaTime);
	FVector CalculateInitialVelocity() const;
	float CalculateGravity() const;

private:
	UJumpingMovementStateData* Data;
	FVector InitialPosition;
	FVector InitialVelocity;
	float ElapsedTime;
	float JumpGravity;
};
