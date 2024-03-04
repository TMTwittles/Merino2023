// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterMovement/MovementStates/AirMovementState.h"

#include "MerinoGameplayStatics.h"
#include "CharacterMovement/MerinoMovementComponent.h"
#include "CharacterMovement/MovementStateControllerComponent.h"
#include "CharacterMovement/MovementStates/MerinoMovementStateKey.h"

void UAirMovementState::PostConfigure(UMovementStateData* _Data)
{
	AirData = Cast<UAirMovementStateData>(_Data);
}

void UAirMovementState::Tick(float DeltaTime)
{
	if (MovementComponent->Velocity.Z < 0.0f && MovementComponent->CharacterGrounded())
	{
		Controller->SetActiveMovementState(EStateID::Grounded);
		return;
	}
}

void UAirMovementState::OnEnter()
{
	CurrentAirMovementVector = FVector::Zero();
	LastActiveAirMovementVector = FVector::Zero();
}

FVector UAirMovementState::CalculateAirControlVector(FVector AirControlDirection, float DeltaTime)
{
	FVector InputVector = AirControlDirection;
	if (InputVector == FVector::Zero())
	{
		float Alpha = UMerinoGameplayStatics::CalculateDecelerationTime(&LastActiveAirMovementVector, &CurrentAirMovementVector, AirData->AirControlDeceleration * DeltaTime);
		CurrentAirMovementVector = FMath::Lerp(CurrentAirMovementVector, FVector::Zero(), Alpha);
	}
	else
	{
		CurrentAirMovementVector = (InputVector * AirData->AirControlAcceleration) * DeltaTime;
		LastActiveAirMovementVector = MovementComponent->Velocity;
		LastActiveAirMovementVector.Z = 0.0f;
	}
	return CurrentAirMovementVector;
}
