// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\..\Public\CharacterMovement\MovementStates\MerinoMovementState.h"
#include "CharacterMovement/MerinoMovementComponent.h"

UMerinoMovementState::UMerinoMovementState()
{
}

UMerinoMovementState::UMerinoMovementState(UMerinoMovementComponent* _PawnMovementComponent)
{
	MovementComponent = _PawnMovementComponent;
}

void UMerinoMovementState::ConfigureMovementState(UMerinoMovementComponent* _MovementComponent)
{
	MovementComponent = _MovementComponent;
}

void UMerinoMovementState::Tick(float DeltaTime)
{
}

void UMerinoMovementState::EnterMovementState()
{
	OnEnter();
}

void UMerinoMovementState::OnEnter()
{
}
