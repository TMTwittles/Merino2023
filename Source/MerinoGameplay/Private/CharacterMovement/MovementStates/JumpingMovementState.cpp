// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterMovement\MovementStates\JumpingMovementState.h"
#include "CharacterMovement/MerinoMovementComponent.h"
#include "CharacterMovement/MovementStateData/JumpingMovementStateData.h"

void UJumpingMovementState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickJump(DeltaTime);
	MovementComponent->UpdateComponentVelocity();
	MovementComponent->MoveUpdatedComponent(MovementComponent->Velocity, MovementComponent->UpdatedActorRotation, false);
}

void UJumpingMovementState::OnEnter()
{
	Super::OnEnter();
	MovementComponent->Velocity += CalculateInitialJumpVelocity();
	AppliedAirControl = false;
}

void UJumpingMovementState::PostConfigure(UMovementStateData* _Data)
{
	Super::PostConfigure(_Data);
	Data = Cast<UJumpingMovementStateData>(_Data);
}

void UJumpingMovementState::TickJump(float DeltaTime)
{
	MovementComponent->Velocity += -MovementComponent->GetOwner()->GetActorUpVector() * Data->Gravity * DeltaTime;
	ApplyHorizontalAirControl(DeltaTime);
}

void UJumpingMovementState::ApplyHorizontalAirControl(float DeltaTime)
{
	FVector HorizontalAirControl = CalculateAirControlVector(FVector::Zero(), DeltaTime);
	// Only apply zero air control once a non-zero air control vector is applied to the components
	// velocity. 
	if (AppliedAirControl || HorizontalAirControl != FVector::Zero())
	{
		MovementComponent->Velocity.X = HorizontalAirControl.X;
		MovementComponent->Velocity.Y = HorizontalAirControl.Y;
		AppliedAirControl = true;
	}
}

FVector UJumpingMovementState::CalculateInitialJumpVelocity() const
{
	return MovementComponent->GetOwner()->GetActorUpVector() * Data->JumpForce;
}

