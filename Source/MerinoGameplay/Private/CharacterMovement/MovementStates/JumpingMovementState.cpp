// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterMovement\MovementStates\JumpingMovementState.h"
#include "MerinoDebugStatics.h"
#include "MerinoLogStatics.h"
#include "CharacterMovement/MerinoMovementComponent.h"
#include "..\..\..\Public\CharacterMovement\MovementStates\MerinoMovementStateKey.h"
#include "CharacterMovement/MovementStateControllerComponent.h"

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
			Controller->SetActiveMovementState(Grounded);
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
	FVector VelNormalized = MovementComponent->Velocity;
	VelNormalized.Normalize();
	FVector ActorLocation = MovementComponent->GetOwner()->GetActorLocation();
	ActorLocation.Z += 50.0f;
	FVector End = ActorLocation + VelNormalized * 10.0f;
	FVector Start02 = End;
	Start02.Z -= 10.0f;
	//End.Z += 50.0f;
	UMerinoLogStatics::LogVector("Velocity: ", MovementComponent->Velocity);
	UMerinoDebugStatics::DrawNonPersistentDebugLine(World, ActorLocation, End, FColor::Red);
	UMerinoDebugStatics::DrawNonPersistentDebugLine(World, End, End, FColor::Green);
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
	MovementComponent->NormalizedJumpProgress = Alpha;
	return FMath::Lerp(MovementComponent->StartingJumpGravity, MovementComponent->MaxJumpGravity, Alpha);
}
