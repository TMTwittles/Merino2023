// Fill out your copyright notice in the Description page of Project Settings.
#include "HSFM/States/GroundedState.h"
#include "CharacterMovement/MerinoMovementComponent.h"

UGroundedState::~UGroundedState()
{
	MovementComponent = nullptr;
}

void UGroundedState::PostInitialise(AActor* Owner)
{
	MovementComponent = Owner->GetComponentByClass<UMerinoMovementComponent>();
}

void UGroundedState::TickState(float DeltaTime)
{
	FVector InputVector = MovementComponent->ConsumeInputVector();
	if (InputVector != FVector::Zero())
	{
		MovementComponent->TickAcceleration(DeltaTime, InputVector);
		MovementComponent->TickRotateToVector(DeltaTime, MovementComponent->Velocity.GetSafeNormal());
	}
	else
	{
		MovementComponent->TickDeceleration(DeltaTime);
	}
	MovementComponent->Update();
}
