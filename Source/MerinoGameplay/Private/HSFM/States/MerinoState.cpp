// Fill out your copyright notice in the Description page of Project Settings.
#include "HSFM/States/MerinoState.h"
#include "HSFM/Transitions/Transition.h"
#include "HSFM/MerinoStateID.h"

void UMerinoState::Initialize(EMerinoStateID InStateID, AActor* InOwner, UWorld* InWorld)
{
	StateID = InStateID;
	World = InWorld;
	PostInitialise(InOwner);
}

void UMerinoState::AddTransition(UTransition* InTransition)
{
	Transitions.Add(InTransition);
}

void UMerinoState::PostInitialise(AActor* InOwner)
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

UMerinoState::~UMerinoState()
{
	World = nullptr;
	for (UTransition* Transition : Transitions)
	{
		delete Transition;
	}
	Transitions.Empty();
}
