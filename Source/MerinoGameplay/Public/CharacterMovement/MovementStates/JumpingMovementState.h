// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "AirMovementState.h"
#include "MerinoMovementState.h"
#include "JumpingMovementState.generated.h"

class UJumpingMovementStateData;
/**
 * 
 */
UCLASS(BlueprintType)
class MERINOGAMEPLAY_API UJumpingMovementState : public UAirMovementState
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnEnter() override;
	virtual void PostConfigure(UMovementStateData* _Data) override;
	
private:
	void TickJump(float DeltaTime);
	void ApplyHorizontalAirControl(float DeltaTime);
	FVector CalculateInitialJumpVelocity() const;
	void CalculateJumpHeights();
	void TickNormalizedJumpProgress();

public:
	UPROPERTY(BlueprintReadOnly)
	float NormalizedJumpProgress;
	
private:
	UPROPERTY()
	UJumpingMovementStateData* JumpingData;
	float ElapsedTime;
	float StartJumpHeight;
	float MaxJumpHeight;
	bool AppliedAirControl = false;
};
