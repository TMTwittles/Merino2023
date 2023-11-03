// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterMovement\MovementStates\JumpingMovementState.h"
#include "CharacterMovement/MerinoMovementComponent.h"
#include "CharacterMovement/MovementStates/MerinoMovementStates.h"

void UJumpingMovementState::Tick(float DeltaTime)
{
	FVector InputVector = MovementComponent->ConsumeInputVector();
	JumpVelocityClamped = MovementComponent->Velocity + InputVector * MovementComponent->AirControl;
	if (MovementComponent->Velocity.Z > 0.0f)
	{
		JumpVelocityClamped.Z -= CalculateUpwardsJumpGravity();
	}
	else
	{
		if (MovementComponent->CharacterGrounded())
		{
			MovementComponent->SetActiveMovementState(Grounded);
			return;
		}
		JumpVelocityClamped.Z -= MovementComponent->Gravity;
		JumpVelocityClamped = JumpVelocityClamped.GetClampedToSize(0.0f, MovementComponent->MaxFallingSpeed);
	}
	MovementComponent->Velocity = JumpVelocityClamped;
	if (InputVector != FVector::Zero())
	{
		FVector VectorToFace = MovementComponent->Velocity;
		VectorToFace.Z = 0.0f;
		MovementComponent->TickRotateToVector(DeltaTime, VectorToFace);
	}
	MovementComponent->UpdateComponentVelocity();
	MovementComponent->MoveUpdatedComponent(MovementComponent->Velocity, MovementComponent->UpdatedActorRotation, false);
}

void UJumpingMovementState::OnEnter()
{
	JumpGravityLerped = MovementComponent->StartingJumpGravity;
	StartingJumpHeight = MovementComponent->GetOwner()->GetActorLocation().Z;
	CurrentJumpDistance = 0.0f;
	MovementComponent->Velocity.Z = 2 * MovementComponent->StartingJumpGravity * FMath::Sqrt(MovementComponent->MaxJumpHeight);
}

float UJumpingMovementState::CalculateUpwardsJumpGravity()
{
	CurrentJumpDistance = MovementComponent->GetOwner()->GetActorLocation().Z;
	float Alpha = 0;
	float ElapsedJumpDistance = CurrentJumpDistance - StartingJumpHeight;
	if (ElapsedJumpDistance > 0)
	{
		Alpha = 1 - (MovementComponent->MaxJumpHeight / ElapsedJumpDistance);
	}
	return FMath::Lerp(MovementComponent->StartingJumpGravity, MovementComponent->MaxJumpGravity, Alpha);
}
