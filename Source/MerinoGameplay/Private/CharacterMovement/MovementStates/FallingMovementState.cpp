// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterMovement/MovementStates/FallingMovementState.h"
#include "CharacterMovement/MerinoMovementComponent.h"
#include "CharacterMovement/MovementStates/MerinoMovementStates.h"

UFallingMovementState::UFallingMovementState()
{
}

void UFallingMovementState::Tick(float DeltaTime)
{
	if (MovementComponent->CharacterGrounded())
	{
		MovementComponent->SetActiveMovementState(Grounded);
		return;
	}

	MovementComponent->Velocity = FVector(MovementComponent->Velocity.X, MovementComponent->Velocity.Y, -MovementComponent->Gravity);
	MovementComponent->UpdateComponentVelocity();
	MovementComponent->MoveUpdatedComponent(MovementComponent->Velocity, MovementComponent->GetOwner()->GetActorRotation(), false);
}
