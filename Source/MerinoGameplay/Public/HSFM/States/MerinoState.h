// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MerinoState.generated.h"

enum EMerinoStateID : int;
class UTransitionRule;
class UMerinoStateMachineComponent;
class UTransitionData;
class UStateActivationCondition;
class UTransition;
/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class MERINOGAMEPLAY_API UMerinoState : public UObject
{
	GENERATED_BODY()

public:
	~UMerinoState() override;
	void Initialize(EMerinoStateID InStateID, AActor* InOwner, UWorld* InWorld);
	virtual void AddTransition(UTransition* InTransition);
	virtual void TickState(float DeltaTime);
	virtual void ExitState();
	virtual void EnterState();
	EMerinoStateID GetStateID() const;
protected:
	virtual void PostInitialise(AActor* InOwner);

protected:
	UPROPERTY()
	TObjectPtr<UWorld> World;

private:
	UPROPERTY()
	TArray<TObjectPtr<UTransition>> Transitions;
	UPROPERTY()
	TEnumAsByte<EMerinoStateID> StateID;
};
