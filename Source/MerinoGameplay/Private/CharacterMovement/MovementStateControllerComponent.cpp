// Fill out your copyright notice in the Description page of Project Settings.
#include "MerinoGameplay/Public/CharacterMovement/MovementStateData/MovementStateData.h"
#include "MerinoGameplay/Public/CharacterMovement/MovementStates/MerinoMovementState.h"
#include "MerinoGameplay/Public/CharacterMovement/MerinoMovementComponent.h"
#include "MerinoGameplay/Public/CharacterMovement/MovementStateControllerComponent.h"
#include "MerinoLogStatics.h"
#include "CharacterMovement/MovementStates/GroundedMovementState.h"
#include "CharacterMovement/MovementStates/MerinoMovementStateKey.h"

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
		TEnumAsByte<EMerinoMovementStateKey> Key = Data->MovementStateKey;
		if (MovementStateMap.Contains(Key) == false)
		{
			BuildMovementState(Data);
			MovementStateMap[Key]->ConfigureMovementState(this, Data, MovementComponent, GetWorld());
		}
	}
}

void UMovementStateControllerComponent::SetActiveMovementState(EMerinoMovementStateKey NewActiveMovementStateKey)
{
	TEnumAsByte<EMerinoMovementStateKey> Key = NewActiveMovementStateKey;
	if (MovementStateMap.Contains(Key))
	{
		ActiveMovementState = MovementStateMap[Key];
		ActiveMovementState->EnterMovementState();
	}
}

void UMovementStateControllerComponent::BuildMovementState(UMovementStateData* Data)
{
	switch (Data->MovementStateKey)
	{
	case Grounded:
		MovementStateMap.Add(Grounded, NewObject<UGroundedMovementState>());
		break;
	}
}
