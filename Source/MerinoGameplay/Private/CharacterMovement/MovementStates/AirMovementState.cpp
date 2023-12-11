// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterMovement/MovementStates/AirMovementState.h"

#include "MerinoGameplayStatics.h"
#include "CharacterMovement/MerinoMovementComponent.h"
#include "CharacterMovement/MovementStateControllerComponent.h"
#include "CharacterMovement/MovementStates/MerinoMovementStateKey.h"

void UAirMovementState::PostConfigure(UMovementStateData* _Data)
{
	Data = Cast<UAirMovementStateData>(_Data);
}

void UAirMovementState::Tick(float DeltaTime)
{
	if (MovementComponent->Velocity.Z < 0.0f && MovementComponent->CharacterGrounded())
	{
		Controller->SetActiveMovementState(EMerinoMovementStateKey::Grounded);
		return;
	}
}

void UAirMovementState::OnEnter()
{
	PrevAirMovementVector = FVector::Zero();
	CurrentAirMovementVector = FVector::Zero();
	LastActiveAirMovementVector = FVector::Zero();
}

FVector UAirMovementState::CalculateAirControlVector(FVector CurrentVelocity, float DeltaTime)
{
	FVector InputVector = MovementComponent->ConsumeInputVector();
	if (InputVector == FVector::Zero())
	{
		float Alpha = UMerinoGameplayStatics::CalculateDecelerationTime(&LastActiveAirMovementVector, &CurrentAirMovementVector, Data->AirControlDeceleration * DeltaTime);
		CurrentAirMovementVector = FMath::Lerp(CurrentAirMovementVector, FVector::Zero(), Alpha);
	}
	else
	{
		CurrentAirMovementVector = PrevAirMovementVector + (InputVector * Data->AirControlAcceleration) * DeltaTime;
		CurrentAirMovementVector = CurrentAirMovementVector.GetClampedToSize(0.0f, Data->MaxAirControlSpeed);
		LastActiveAirMovementVector = CurrentAirMovementVector;
	}
	PrevAirMovementVector = CurrentAirMovementVector;
	return CurrentAirMovementVector;
}
