// Fill out your copyright notice in the Description page of Project Settings.
#include "HSFM/Transitions/Transition.h"
#include "HSFM/Transitions/TransitionRule.h"


void UTransition::InitializeTransition(UMerinoStateMachineComponent* InStateMachineComponent, TArray<TSubclassOf<UTransitionRule>>* InTransitionRuleClasses, UMerinoState* InTransitionState)
{
	StateMachineComponent = InStateMachineComponent;
	TransitionState = InTransitionState;

	// Build transition rules.
	for (TSubclassOf<UTransitionRule> TransitionRuleClass : *InTransitionRuleClasses)
	{
		TObjectPtr<UTransitionRule> TransitionRule = NewObject<UTransitionRule>(this, TransitionRuleClass);
		TransitionRule->ConfigureTransitionRule(StateMachineComponent->GetOwner());
		TransitionRules.Add(TransitionRule);
	}
}

void UTransition::Transition()
{
	StateMachineComponent->TransitionToState(TransitionState);
}

void UTransition::TickTransition(float DeltaTime, UWorld* World)
{
	// In order to transition all transition rules must be met.
	bool bShouldTransition = true;
	for (UTransitionRule* TransitionRule : TransitionRules)
	{
		if (bShouldTransition == false)
		{
			break;
		}

		TransitionRule->TickTransitionRule(DeltaTime, World);
		bShouldTransition = TransitionRule->ShouldTransition();
	}
	
	if (bShouldTransition)
	{
		Transition();
	}
}
