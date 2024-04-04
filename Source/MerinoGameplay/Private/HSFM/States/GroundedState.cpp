// Fill out your copyright notice in the Description page of Project Settings.
#include "HSFM/States/GroundedState.h"
#include "CharacterMovement/MerinoMovementComponent.h"

void UGroundedState::TickState(float DeltaTime)
{
	FVector InputVector = MovementComponent->ConsumeInputVector();
	if (InputVector != FVector::Zero())
	{
		FVector InputVectorNormalized = InputVector.GetSafeNormal();
		MovementComponent->TickAcceleration(InputVectorNormalized);
		MovementComponent->TickRotateToVector(DeltaTime, InputVectorNormalized);
	}
	else
	{
		MovementComponent->TickDeceleration(DeltaTime);
	}
	MovementComponent->Update();
}
