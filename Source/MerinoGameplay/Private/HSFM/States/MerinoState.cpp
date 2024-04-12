// Fill out your copyright notice in the Description page of Project Settings.
#include "HSFM/States/MerinoState.h"
#include "HSFM/Transitions/Transition.h"
#include "HSFM/MerinoStateID.h"
#include "HSFM/StateProperties/MerinoStateProperties.h"

void UMerinoState::Initialize(EMerinoStateID InStateID, AActor* InOwner, UWorld* InWorld, UMerinoStateProperties* InStateProperties)
{
	StateID = InStateID;
	World = InWorld;
	PostInitialise(InOwner, InStateProperties);
}

void UMerinoState::AddTransition(UTransition* InTransition)
{
	Transitions.Add(InTransition);
}

TArray<TObjectPtr<UTransition>>* UMerinoState::GetTransitions()
{
	return &Transitions;
}

void UMerinoState::PostInitialise(AActor* InOwner, UMerinoStateProperties* InStateProperties)
{
}

void UMerinoState::TickState(float DeltaTime)
{
}

void UMerinoState::ExitState()
{
}

void UMerinoState::EnterState()
{
}

EMerinoStateID UMerinoState::GetStateID() const
{
	return StateID;
}
