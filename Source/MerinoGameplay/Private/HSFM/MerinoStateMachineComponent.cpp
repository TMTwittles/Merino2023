// Fill out your copyright notice in the Description page of Project Settings.
#include "HSFM\MerinoStateMachineComponent.h"
#include "HSFM\States\MerinoState.h"
#include "HSFM\StateData\StateData.h"
#include "HSFM\Transitions\TransitionRule.h"
#include "HSFM\Transitions\Transition.h"
#include "HSFM\StateProperties\MerinoStateProperties.h"
#include "HSFM\StateProperties\StatePropertyDataReader.h"
#include "HSFM\MerinoStateID.h"

// Sets default values for this component's properties
UMerinoStateMachineComponent::UMerinoStateMachineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UMerinoStateMachineComponent::BeginPlay()
{
	Super::BeginPlay();
	ConstructStates();
}

void UMerinoStateMachineComponent::ConstructStates()
{
	// We first construct each state.
	for (UStateData* StateData : StateDatas)
	{
		TObjectPtr<UMerinoState> ConstructedState = NewObject<UMerinoState>(this, StateData->State, StateData->StateName);
		EMerinoStateID StateID = StateData->StateID;
		TObjectPtr<UMerinoStateProperties> StateProperties = NewObject<UMerinoStateProperties>();
		StateProperties->Initialize(StateID);
		UStatePropertyDataReader::ReadFromGlobalStateProperties(GlobalStateProperties, StateProperties);
		ConstructedState->Initialize(StateID, GetOwner(), GetWorld(), StateProperties);
		States.Add(StateID, ConstructedState);
	}
	
	// Once all states have been constructed, build and add transitions to the constructed
	// states. 
	for (UStateData* StateData : StateDatas)
	{
		UMerinoState* State = States[StateData->StateID];

		for (UTransitionData* TransitionData : StateData->Transitions)
		{
			TObjectPtr<UTransition> Transition = NewObject<UTransition>();
			TObjectPtr<UTransitionRule> TransitionRule = NewObject<UTransitionRule>(TransitionData->TransitionRule);
			TObjectPtr<UMerinoState> TransitionState = States[TransitionData->TransitionStateID];
			Transition->InitializeTransition(this, TransitionRule, TransitionState);
			State->AddTransition(Transition);
		}
	}

	OnStatesInitialized.Broadcast();
	
	// Set default active state to arbitrary first state. 
	TransitionToState(States[StateDatas[0]->StateID]);
}


// Called every frame
void UMerinoStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (ActiveState != nullptr)
	{
		ActiveState->TickState(DeltaTime);
	}
}

void UMerinoStateMachineComponent::TransitionToState(UMerinoState* TransitionState)
{
	if (ActiveState != nullptr)
	{
		ActiveState->ExitState();
	}
	ActiveState = TransitionState;
	ActiveState->EnterState();
	OnActiveStateChanged.Broadcast(ActiveState->GetStateID());
}


