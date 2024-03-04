// Fill out your copyright notice in the Description page of Project Settings.


#include "HSFM/Transitions/TransitionRule.h"

bool UTransitionRule::ShouldTransition()
{
	return bShouldTransition;
}

void UTransitionRule::SetShouldTransition(bool bInShouldTransition)
{
	bShouldTransition = bInShouldTransition;
}

void UTransitionRule::ConfigureTransitionRule_Implementation(AActor* InOwner)
{
}

void UTransitionRule::TickTransitionRule_Implementation(float DeltaTime)
{
}


