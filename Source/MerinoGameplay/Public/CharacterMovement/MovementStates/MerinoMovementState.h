// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "MerinoMovementState.generated.h"

class UBehaviourController;
class UMovementStateBehaviour;
enum EMovementStateBehaviourKey : int;
class UMovementStateControllerComponent;
class UMovementStateData;
enum EMerinoMovementStateKey : int;
class UMerinoMovementComponent;

UCLASS(BlueprintType, Abstract)
class MERINOGAMEPLAY_API UMerinoMovementState : public UObject
{
	GENERATED_BODY()
public:
	UMerinoMovementState();
	void ConfigureMovementState(UBehaviourController* _BehaviourController, UMovementStateControllerComponent* _MSController, UMovementStateData* _Data, UMerinoMovementComponent* _MovementComponent, UWorld* _World);
	virtual void Tick(float DeltaTime);
	void EnterMovementState();
	void AddBehaviour(TEnumAsByte<EMovementStateBehaviourKey> InKey, UMovementStateBehaviour* InBehaviour);
	
protected:
	virtual void OnEnter();
	virtual void PostConfigure(UMovementStateData* Data);
	template <typename TMovementStateBehaviour>
	TMovementStateBehaviour* GetBehaviour(TEnumAsByte<EMovementStateBehaviourKey> InKey);

public:
	UPROPERTY()
	UBehaviourController* BehaviourController;
	UPROPERTY()
	UMovementStateControllerComponent* Controller;
	UPROPERTY()
	UMerinoMovementComponent* MovementComponent;
	UPROPERTY()
	UWorld* World;

protected:
	UPROPERTY()
	TMap<TEnumAsByte<EMovementStateBehaviourKey>, UMovementStateBehaviour*> BehaviourMap;
};
