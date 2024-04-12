// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "HSFM/States/MovementState.h"
#include "JumpingState.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MERINOGAMEPLAY_API UJumpingState : public UMovementState
{
	GENERATED_BODY()

public:
	virtual void EnterState();
	virtual void TickState(float DeltaTime);

protected:
	virtual void PostInitialise(AActor* InOwner, UMerinoStateProperties* InStateProperties);

private:
	void CalculateJumpAttributes();
	void TickNormalizedJumpProgress();
	FVector CalculateJumpDirection();

public:
	/// <summary>
	/// Attributes primarily used in BP for determining jump progress. i.e How close to peak etc. 
	/// </summary>
	UPROPERTY(BlueprintReadOnly)
	float NormalizedJumpProgress;

private:
	UPROPERTY()
	TObjectPtr<AActor> Owner;
	UPROPERTY()
	float JumpForce;
	UPROPERTY()
	float StartJumpHeight;
	UPROPERTY()
	float MaxJumpHeight;
	UPROPERTY()
	float InitialJumpAngle;
};
