// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterMovement\MovementStates\JumpingMovementState.h"
#include "MerinoMathStatics.h"
#include "CharacterMovement/MerinoMovementComponent.h"
#include "CharacterMovement/MovementStateData/JumpingMovementStateData.h"

void UJumpingMovementState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickJump(DeltaTime);
	//MovementComponent->UpdateComponentVelocity();
	//MovementComponent->MoveUpdatedComponent(MovementComponent->Velocity, MovementComponent->UpdatedActorRotation, false);
}

void UJumpingMovementState::OnEnter()
{
	MovementComponent->Velocity += CalculateInitialJumpVelocity();
	AppliedAirControl = false;
	CalculateJumpHeights();
	TickNormalizedJumpProgress();
}

void UJumpingMovementState::PostConfigure(UMovementStateData* _Data)
{
	Super::PostConfigure(_Data);
	JumpingData = Cast<UJumpingMovementStateData>(_Data);
}

void UJumpingMovementState::TickJump(float DeltaTime)
{
	MovementComponent->Velocity += -MovementComponent->GetOwner()->GetActorUpVector() * JumpingData->Gravity * DeltaTime;
	ApplyHorizontalAirControl(DeltaTime);
	TickNormalizedJumpProgress();
}

void UJumpingMovementState::ApplyHorizontalAirControl(float DeltaTime)
{
	FVector InputDirection = MovementComponent->ConsumeInputVector();
	FVector HorizontalAirControl = CalculateAirControlVector(InputDirection, DeltaTime);
	// Only apply zero air control once a non-zero air control vector is applied to the components
	// velocity. 
	if (AppliedAirControl || HorizontalAirControl != FVector::Zero())
	{
		FVector HorizontalJumpVelocity = MovementComponent->Velocity;
		HorizontalJumpVelocity.Z = 0.0f;
		HorizontalJumpVelocity.X += HorizontalAirControl.X;
		HorizontalJumpVelocity.Y += HorizontalAirControl.Y;
		FVector HorizontalJumpVelocityClamped = HorizontalJumpVelocity.GetClampedToSize(0.0f, JumpingData->MaxAirControlSpeed);
		MovementComponent->Velocity.X = HorizontalJumpVelocityClamped.X;
		MovementComponent->Velocity.Y = HorizontalJumpVelocityClamped.Y;
		AppliedAirControl = true;
	}
	if (InputDirection != FVector::Zero())
	{
		//MovementComponent->TickRotateToVector(DeltaTime, InputDirection);
	}
}

FVector UJumpingMovementState::CalculateInitialJumpVelocity() const
{
	return MovementComponent->GetOwner()->GetActorUpVector() * JumpingData->JumpForce;
}

void UJumpingMovementState::CalculateJumpHeights()
{
	StartJumpHeight = MovementComponent->GetActorLocation().Z;
	float JumpAngle = UMerinoMathStatics::GetUnsignedAngleBetweenTwoVectors(
			MovementComponent->GetOwner()->GetActorForwardVector(),
			MovementComponent->Velocity.GetSafeNormal());
	FVector InitialJumpVelocity = MovementComponent->Velocity * FMath::Sin(JumpAngle);
	float YInitialJumpVelocity = InitialJumpVelocity.Z;
	MaxJumpHeight = (YInitialJumpVelocity * YInitialJumpVelocity) / (2 * (JumpingData->Gravity * World->GetDeltaSeconds()));
	MaxJumpHeight += StartJumpHeight;
}

void UJumpingMovementState::TickNormalizedJumpProgress()
{
	NormalizedJumpProgress = (MovementComponent->GetActorLocation().Z - StartJumpHeight) / (MaxJumpHeight - StartJumpHeight);
	NormalizedJumpProgress = FMath::Clamp(NormalizedJumpProgress, 0.0f, 1.0f);
}

