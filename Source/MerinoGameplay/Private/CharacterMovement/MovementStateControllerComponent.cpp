// Fill out your copyright notice in the Description page of Project Settings.
#include "MerinoGameplay/Public/CharacterMovement/MovementStateControllerComponent.h"
#include "CharacterMovement/MovementStates/FallingMovementState.h"
#include "MerinoGameplay/Public/CharacterMovement/MovementStateData/MovementStateData.h"
#include "MerinoGameplay/Public/CharacterMovement/MovementStates/MerinoMovementState.h"
#include "MerinoGameplay/Public/CharacterMovement/MerinoMovementComponent.h"
#include "CharacterMovement/MovementStates/GroundedMovementState.h"
#include "CharacterMovement/MovementStates/JumpingMovementState.h"
#include "CharacterMovement/MovementStates/MerinoMovementStateKey.h"
#include "CharacterMovement/MovementStates/MovementStateBehaviours/BehaviourController.h"
#include "CharacterMovement/MovementStates/MovementStateBehaviours/LockOnMovementStateBehaviour.h"
#include "CharacterMovement/MovementStates/MovementStateBehaviours/MovementStateBehaviour.h"
#include "CharacterMovement/MovementStates/MovementStateBehaviours/MovementStateBehaviourKey.h"

void UMovementStateControllerComponent::BeginPlay()
{
	Super::BeginPlay();
	Configure();
	SetActiveMovementState(Grounded);
}

void UMovementStateControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (ActiveMovementState != nullptr)
	{
		ActiveMovementState->Tick(DeltaTime);
	}
}

void UMovementStateControllerComponent::Configure()
{
	UMerinoMovementComponent* MovementComponent = GetOwner()->GetComponentByClass<UMerinoMovementComponent>();
	for (UMovementStateData* Data : MovementStates)
	{
		TEnumAsByte<EStateID> Key = Data->MovementStateKey;
		UMerinoMovementState* MovementState = BuildMovementState(Data);
		if (MovementStateMap.Contains(Key) == false && MovementState != nullptr)
		{
			MovementStateMap.Add(Key, MovementState);
			UBehaviourController* BehaviourController = BuildBehaviourController(MovementState, Data);
			MovementStateMap[Key]->ConfigureMovementState(BehaviourController, this, Data, MovementComponent, GetWorld());
		}
	}
	OnMovementStatesConstructed.Broadcast();
}

void UMovementStateControllerComponent::SetActiveMovementState(EStateID NewActiveMovementStateKey)
{
	TEnumAsByte<EStateID> Key = NewActiveMovementStateKey;
	if (MovementStateMap.Contains(Key))
	{
		ActiveMovementState = MovementStateMap[Key];
		OnMovementStateChanged.Broadcast(Key);
		ActiveMovementState->EnterMovementState();
	}
}

UMerinoMovementState* UMovementStateControllerComponent::GetActiveMovementState()
{
	return ActiveMovementState;
}

UMerinoMovementState* UMovementStateControllerComponent::GetMovementState(EStateID Key)
{
	return MovementStateMap[Key];
}

// TODO: Move this to static factory methods. 
UMerinoMovementState* UMovementStateControllerComponent::BuildMovementState(UMovementStateData* Data) const
{
	UMerinoMovementState* MovementState = nullptr;
	switch (Data->MovementStateKey)
	{
	case Grounded:
		MovementState = NewObject<UGroundedMovementState>();
		break;
	case Falling:
		MovementState = NewObject<UFallingMovementState>();
		break;
	case Jumping:
		MovementState = NewObject<UJumpingMovementState>();
		break;
	}
	return MovementState;
}

UBehaviourController* UMovementStateControllerComponent::BuildBehaviourController(UMerinoMovementState* ParentState, UMovementStateData* Data) const
{
	UBehaviourController* Controller = NewObject<UBehaviourController>();
	Controller->Initialize(ParentState);
	for (EMovementStateBehaviourKey Key : Data->Behaviours)
	{
		Controller->AddBehaviour(Key, BuildMovementStateBehaviour(Key));
	}
	return Controller;
}

UMovementStateBehaviour* UMovementStateControllerComponent::BuildMovementStateBehaviour(EMovementStateBehaviourKey Key) const
{
	UMovementStateBehaviour* ConstructedBehaviour = nullptr;
	switch (Key)
	{
	case LockOn:
		ConstructedBehaviour = NewObject<ULockOnMovementStateBehaviour>();
		break;
	}
	return ConstructedBehaviour;
}


