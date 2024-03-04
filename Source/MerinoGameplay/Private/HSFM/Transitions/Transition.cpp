// Fill out your copyright notice in the Description page of Project Settings.
#include "HSFM/Transitions/Transition.h"
#include "HSFM/Transitions/TransitionRule.h"


void UTransition::InitializeTransition(UMerinoStateMachineComponent* InStateMachineComponent, UTransitionRule* InTransitionRule, UMerinoState* InTransitionState)
{
	TransitionRule = InTransitionRule;
	StateMachineComponent = InStateMachineComponent;
	TransitionState = InTransitionState;
	TransitionRule->ConfigureTransitionRule(StateMachineComponent->GetOwner());
}

void UTransition::Transition()
{
	StateMachineComponent->TransitionToState(TransitionState);
}

void UTransition::TickTransition(float DeltaTime)
{
	TransitionRule->TickTransitionRule(DeltaTime);
	if (TransitionRule->ShouldTransition())
	{
		Transition();
	}
}
