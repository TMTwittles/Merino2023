// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterMovement\MovementStates\JumpingMovementState.h"

#include "MerinoLogStatics.h"
#include "CharacterMovement/MerinoMovementComponent.h"
#include "CharacterMovement/MovementStateData/JumpingMovementStateData.h"

void UJumpingMovementState::Tick(float DeltaTime)
{
	TickJump(DeltaTime);
	MovementComponent->UpdateComponentVelocity();
	MovementComponent->MoveUpdatedComponent(MovementComponent->Velocity, MovementComponent->UpdatedActorRotation, false);
}

void UJumpingMovementState::OnEnter()
{
	LateralVelocity = MovementComponent->Velocity;
	LateralVelocity.Z = 1.0f;
	MovementComponent->Velocity = CalculateInitialVelocity();
	UMerinoLogStatics::LogVector("Initial velocity: ", MovementComponent->Velocity);
}

void UJumpingMovementState::PostConfigure(UMovementStateData* _Data)
{
	Data = Cast<UJumpingMovementStateData>(_Data);
	JumpGravity = CalculateGravity();
	UMerinoLogStatics::LogFloat("Jump gravity: ", MovementComponent->MaxJumpGravity);
}

void UJumpingMovementState::TickJump(float DeltaTime)
{
	FVector JumpGravityVector = FVector(0.0f, 0.0f, CalculateGravity());
	MovementComponent->Velocity += 2.0f * JumpGravityVector * (DeltaTime);
	UMerinoLogStatics::LogFloat("Jump gravity: ", JumpGravity);
	UMerinoLogStatics::LogFloat("Delta time: ", DeltaTime);
	UMerinoLogStatics::LogVector("JumpGravity: ", JumpGravityVector);
	UMerinoLogStatics::LogVector("Velocity ticked: ", MovementComponent->Velocity);
}

FVector UJumpingMovementState::CalculateInitialVelocity() const
{
	return (2 * Data->MaxJumpHeight * LateralVelocity) / Data->MaxDistanceFromPeakJumpHeight;
}

float UJumpingMovementState::CalculateGravity() const
{
	return (-2.0f * (Data->MaxJumpHeight * LateralVelocity) / Data->MaxDistanceFromPeakJumpHeight).Z;
}

