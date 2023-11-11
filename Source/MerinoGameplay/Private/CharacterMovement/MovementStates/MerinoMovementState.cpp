// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterMovement\MovementStates\MerinoMovementState.h"
#include "CharacterMovement/MovementStateControllerComponent.h"
#include "CharacterMovement/MerinoMovementComponent.h"

UMerinoMovementState::UMerinoMovementState()
{
}

void UMerinoMovementState::ConfigureMovementState(
	UMovementStateControllerComponent* _MSController,
	UMovementStateData* _Data,
	UMerinoMovementComponent* _MovementComponent,
	UWorld* _World)
{
	Controller = _MSController;
	MovementComponent = _MovementComponent;
	World = _World;
	PostConfigure(_Data);
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

void UMerinoMovementState::PostConfigure(UMovementStateData* Data)
{
}
