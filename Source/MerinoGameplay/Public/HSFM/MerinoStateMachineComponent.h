﻿// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MerinoStateMachineComponent.generated.h"

enum EMerinoStateID : int;
class UTransitionData;
class UTransition;
class UMerinoState;
class UStateData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStatesInitialized);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActiveStateChanged, EMerinoStateID, StateID);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MERINOGAMEPLAY_API UMerinoStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMerinoStateMachineComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void TransitionToState(UMerinoState* TransitionState);

	// Events
	UPROPERTY(BlueprintAssignable)
	FOnStatesInitialized OnStatesInitialized;
	UPROPERTY(BlueprintAssignable)
	FOnActiveStateChanged OnActiveStateChanged;
	
protected:
	virtual void BeginPlay() override;

private:
	void ConstructStates();

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="True"))
	TArray<UStateData*> StateDatas;
	UPROPERTY()
	UMerinoState* ActiveState;
	UPROPERTY()
	TMap<TEnumAsByte<EMerinoStateID>, UMerinoState*> States;
	UPROPERTY()
	int ActiveStateIndex = 0;
};