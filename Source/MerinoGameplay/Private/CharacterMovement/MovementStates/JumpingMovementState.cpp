// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterMovement\MovementStates\JumpingMovementState.h"
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
	InitialVelocity = CalculateInitialVelocity();
	InitialPosition = MovementComponent->GetOwner()->GetActorLocation();
	ElapsedTime = 0.0f;
}

void UJumpingMovementState::PostConfigure(UMovementStateData* _Data)
{
	Data = Cast<UJumpingMovementStateData>(_Data);
	JumpGravity = CalculateGravity();
}

void UJumpingMovementState::TickJump(float DeltaTime)
{
	FVector TickJumpVelocity = InitialVelocity * ElapsedTime;
	TickJumpVelocity.Z -= 0.5f * JumpGravity * (ElapsedTime * ElapsedTime);
	MovementComponent->Velocity = TickJumpVelocity;
	ElapsedTime += DeltaTime;
}

FVector UJumpingMovementState::CalculateInitialVelocity() const
{
	FVector _InitialVelocity = FVector::Zero();
	_InitialVelocity.Z = Data->CalculateInitialVelocityZ();
	return _InitialVelocity;
}

float UJumpingMovementState::CalculateGravity() const
{
	return Data->CalculateGravity();
}

