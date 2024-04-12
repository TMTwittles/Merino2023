// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "MerinoState.generated.h"

enum EMerinoStateID : int;
class UTransitionRule;
class UMerinoStateMachineComponent;
class UTransitionData;
class UStateActivationCondition;
class UTransition;
class UMerinoStateProperties;

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class MERINOGAMEPLAY_API UMerinoState : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(EMerinoStateID InStateID, AActor* InOwner, UWorld* InWorld, UMerinoStateProperties* InStateProperties);
	void AddTransition(UTransition* InTransition);
	TArray<TObjectPtr<UTransition>>* GetTransitions();
	virtual void TickState(float DeltaTime);
	virtual void ExitState();
	virtual void EnterState();
	EMerinoStateID GetStateID() const;
protected:
	virtual void PostInitialise(AActor* InOwner, UMerinoStateProperties* InStateProperties);

protected:
	UPROPERTY()
	TObjectPtr<UWorld> World;
	UPROPERTY()
	TEnumAsByte<EMerinoStateID> StateID;
private:
	UPROPERTY()
	TArray<TObjectPtr<UTransition>> Transitions;
};
