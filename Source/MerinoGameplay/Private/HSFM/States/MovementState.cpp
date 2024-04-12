// Fill out your copyright notice in the Description page of Project Settings.
#include "HSFM/States/MovementState.h"
#include "CharacterMovement/MerinoMovementComponent.h"
#include "HSFM/StateProperties/MerinoStateProperties.h"
#include "MerinoLogStatics.h"

void UMovementState::PostInitialise(AActor* InOwner, UMerinoStateProperties* InStateProperties)
{
	/*MovementComponent = InOwner->GetComponentByClass<UMerinoMovementComponent>();
	Acceleration = InStateProperties->GetFloatProperty("Acceleration");
	Deceleration = InStateProperties->GetFloatProperty("Deceleration");
	MaxSpeed = InStateProperties->GetFloatProperty("Max speed");
	AngularAcceleration = InStateProperties->GetFloatProperty("Angular Acceleration");
	Gravity = InStateProperties->GetFloatProperty("Gravity");
	MaxFallingSpeed = InStateProperties->GetFloatProperty("Max falling speed");
	MinimumJumpAnglePercentage = InStateProperties->GetFloatProperty("Minimum jump angle percentage");*/
}

void UMovementState::EnterState()
{
	/*MovementComponent->Acceleration = Acceleration;
	MovementComponent->Deceleration = Deceleration;
	MovementComponent->MaxSpeed = MaxSpeed;
	MovementComponent->AngularAcceleration = AngularAcceleration;
	MovementComponent->Gravity = Gravity;
	MovementComponent->MaxFallingSpeed = MaxFallingSpeed;*/
}
