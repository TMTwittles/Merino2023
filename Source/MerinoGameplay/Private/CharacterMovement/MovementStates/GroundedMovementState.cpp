// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterMovement\MovementStates\GroundedMovementState.h"
#include "CharacterMovement\MerinoMovementComponent.h"
#include "CharacterMovement/MovementStates/MerinoMovementStates.h"

UGroundedMovementState::UGroundedMovementState()
{
}

void UGroundedMovementState::Tick(float DeltaTime)
{
	if (MovementComponent->CharacterGrounded() == false)
	{
		MovementComponent->SetActiveMovementState(Falling);
		return;
	}
	
	FVector CurrentInputVector = MovementComponent->ConsumeInputVector();
	MovementComponent->Velocity = CurrentInputVector * MovementComponent->Speed;
	if (CurrentInputVector != FVector::Zero())
	{
		MovementComponent->TickRotateToVector(DeltaTime, CurrentInputVector);
	}
	MovementComponent->UpdateComponentVelocity();
	MovementComponent->MoveUpdatedComponent(MovementComponent->Velocity, MovementComponent->UpdatedActorRotation, false);
}
