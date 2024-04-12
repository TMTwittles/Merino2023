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
		TArray<TSubclassOf<UTransitionRule>>* InTransitionRuleClasses,
		UMerinoState* InTransitionState);
	virtual void TickTransition(float DeltaTime, UWorld* World);
protected:
	void Transition();
	

private:
	UPROPERTY()
	TArray<TObjectPtr<UTransitionRule>> TransitionRules;
	UPROPERTY()
	TObjectPtr<UMerinoStateMachineComponent> StateMachineComponent;
	UPROPERTY()
	TObjectPtr<UMerinoState> TransitionState;
};
