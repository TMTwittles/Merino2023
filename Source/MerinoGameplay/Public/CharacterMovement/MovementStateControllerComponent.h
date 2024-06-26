﻿// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "MovementStateControllerComponent.generated.h"

enum EMovementStateBehaviourKey : int;
class UMovementStateBehaviour;
class UBehaviourController;
class UMerinoMovementComponent;
class UMovementStateData;
enum EStateID : int;
class UMerinoMovementState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMovementStatesConstructed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMovementStateChanged, EStateID, MovementStateKey);

UCLASS(meta=(BlueprintSpawnableComponent))
class MERINOGAMEPLAY_API UMovementStateControllerComponent : public UActorComponent
{
private:
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction) override;
	void Configure();
	void SetActiveMovementState(EStateID NewActiveMovementStateKey);
	UFUNCTION(BlueprintCallable)
	UMerinoMovementState* GetActiveMovementState();
	UFUNCTION(BlueprintCallable)
	UMerinoMovementState* GetMovementState(EStateID Key);
	UPROPERTY(BlueprintAssignable)
	FOnMovementStateChanged OnMovementStateChanged;
	UPROPERTY(BlueprintAssignable)
	FOnMovementStatesConstructed OnMovementStatesConstructed;
	
private:
	UMerinoMovementState* BuildMovementState(UMovementStateData* Data) const;
	UBehaviourController* BuildBehaviourController(UMerinoMovementState* ParentState, UMovementStateData* Data) const;
	UMovementStateBehaviour* BuildMovementStateBehaviour(EMovementStateBehaviourKey Key) const;

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess))
	TArray<UMovementStateData*> MovementStates;
	UPROPERTY()
	TMap<TEnumAsByte<EStateID>, UMerinoMovementState*> MovementStateMap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="True"))
	UMerinoMovementState* ActiveMovementState;
};
