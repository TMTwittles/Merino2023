// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterMovement/MovementStates/MovementStateBehaviours/BehaviourController.h"
#include "CharacterMovement/MovementStates/MovementStateBehaviours/MovementStateBehaviour.h"
#include "CharacterMovement/MovementStates/MovementStateBehaviours/LockOnMovementStateBehaviour.h"

void UBehaviourController::Initialize(UMerinoMovementState* InParentState)
{
	ParentState = InParentState;
}

void UBehaviourController::AddBehaviour(TEnumAsByte<EMovementStateBehaviourKey> InKey, UMovementStateBehaviour* InBehaviour)
{
	BehaviourMap.Add(InKey, InBehaviour);
	BehaviourMap[InKey]->SetParentMovementState(ParentState);
	Behaviours.Add(BehaviourMap[InKey]);
}

void UBehaviourController::TickActiveBehaviours(float DeltaTime)
{
	for (UMovementStateBehaviour* Behaviour : Behaviours)
	{
		if (Behaviour->Active())
		{
			Behaviour->TickBehaviour(DeltaTime);
		}
	}
}

bool UBehaviourController::ContainsBehaviour(TEnumAsByte<EMovementStateBehaviourKey> InKey)
{
	return BehaviourMap.Contains(InKey);
}

void UBehaviourController::SetBehaviourActive(TEnumAsByte<EMovementStateBehaviourKey> InKey, bool bInActiveState)
{
	BehaviourMap[InKey]->SetActive(bInActiveState);
}
