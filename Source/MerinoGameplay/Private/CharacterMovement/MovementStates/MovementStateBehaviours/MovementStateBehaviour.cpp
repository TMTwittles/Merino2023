// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterMovement/MovementStates/MovementStateBehaviours/MovementStateBehaviour.h"
#include "CharacterMovement/MovementStates/MerinoMovementState.h"

void UMovementStateBehaviour::SetParentMovementState(UMerinoMovementState* InMovementState)
{
	MovementState = InMovementState;
}

void UMovementStateBehaviour::TickBehaviour(float DeltaTime)
{
}

void UMovementStateBehaviour::SetActive(bool bActiveState)
{
	bActive = bActiveState;
	if (bActive)
	{
		OnActive();
	}
	else
	{
		OnInActive();
	}
}

bool UMovementStateBehaviour::Active()
{
	return bActive;
}

void UMovementStateBehaviour::OnActive()
{
}

void UMovementStateBehaviour::OnInActive()
{
}
