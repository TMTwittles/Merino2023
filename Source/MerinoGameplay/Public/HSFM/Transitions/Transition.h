// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TransitionRule.h"
#include "HSFM/MerinoStateMachineComponent.h"
#include "..\States\MerinoState.h"
#include "Transition.generated.h"

class UMerinoStateMachineComponent;
class UMerinoState;
/**
 * 
 */
UCLASS()
class MERINOGAMEPLAY_API UTransition : public UObject
{
	GENERATED_BODY()

public:
	void InitializeTransition(
		UMerinoStateMachineComponent* InStateMachineComponent,
		UTransitionRule* InTransitionRule,
		UMerinoState* InTransitionState);

protected:
	void Transition();
	virtual void TickTransition(float DeltaTime);

private:
	UPROPERTY()
	TObjectPtr<UTransitionRule> TransitionRule;
	UPROPERTY()
	TObjectPtr<UMerinoStateMachineComponent> StateMachineComponent;
	UPROPERTY()
	TObjectPtr<UMerinoState> TransitionState;
};
