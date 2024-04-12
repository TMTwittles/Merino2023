// Fill out your copyright notice in the Description page of Project Settings.
#include "HSFM/Transitions/TransitionRule.h"
#include "MerinoLogStatics.h"

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
	UMerinoLogStatics::LogMessage(TEXT("Configure transition rule is being called by {0}"), {this->GetFName().ToString()});
}

void UTransitionRule::TickTransitionRule_Implementation(float DeltaTime, UWorld* World)
{
	
}


