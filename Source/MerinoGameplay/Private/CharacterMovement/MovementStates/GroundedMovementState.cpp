﻿// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterMovement\MovementStates\GroundedMovementState.h"
#include "CharacterMovement\MerinoMovementComponent.h"
#include "..\..\..\Public\CharacterMovement\MovementStates\MerinoMovementStateKey.h"
#include "CharacterMovement/MovementStateControllerComponent.h"


UGroundedMovementState::UGroundedMovementState()
{
}

void UGroundedMovementState::OnEnter()
{
	LastActiveVelocity = FVector::Zero();
	MovementComponent->Velocity = FVector::Zero();
}

float UGroundedMovementState::CalculateNormalizedElapsedDecelerationTime()
{
	float TotalDecelerationTime = (float)LastActiveVelocity.Size() / MovementComponent->Deceleration;
	float ElapsedDecelerationTime = (MovementComponent->Velocity.Size() - MovementComponent->Deceleration) / MovementComponent->Deceleration;
	ElapsedDecelerationTime = TotalDecelerationTime - ElapsedDecelerationTime;
	return ElapsedDecelerationTime / TotalDecelerationTime;
}

void UGroundedMovementState::Tick(float DeltaTime)
{
	if (MovementComponent->CharacterGrounded() == false)
	{
		Controller->SetActiveMovementState(Falling);
		return;
	}
	
	FVector CurrentInputVector = MovementComponent->ConsumeInputVector();
	FVector ClampedVelocity = FVector::Zero();
	if (CurrentInputVector != FVector::Zero())
	{
		if (LastActiveVelocity != FVector::Zero())
		{
			LastActiveVelocity = FVector::Zero();
		}
		ClampedVelocity = MovementComponent->Velocity + CurrentInputVector * MovementComponent->Acceleration;
		MovementComponent->TickRotateToVector(DeltaTime, ClampedVelocity);
	}
	else
	{
		if (MovementComponent->Velocity == FVector::Zero())
		{
			return;
		}
		
		if (LastActiveVelocity == FVector::Zero())
		{
			LastActiveVelocity = MovementComponent->Velocity;
		}
		float Alpha = CalculateNormalizedElapsedDecelerationTime();
		ClampedVelocity = FMath::Lerp(MovementComponent->Velocity, FVector::Zero(), Alpha);
	}
	ClampedVelocity = ClampedVelocity.GetClampedToSize(0.0f, MovementComponent->MaxSpeed);
	MovementComponent->Velocity = ClampedVelocity;
	MovementComponent->UpdateComponentVelocity();
	MovementComponent->MoveUpdatedComponent(MovementComponent->Velocity, MovementComponent->UpdatedActorRotation, false);
}