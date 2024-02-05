// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BehaviourController.generated.h"

class UMovementStateBehaviour;
class UMerinoMovementState;
enum EMovementStateBehaviourKey : int;
/**
 * 
 */
UCLASS()
class MERINOGAMEPLAY_API UBehaviourController : public UObject
{
private:
	GENERATED_BODY()

public:
	void Initialize(UMerinoMovementState* InParentState);
	void AddBehaviour(TEnumAsByte<EMovementStateBehaviourKey> InKey, UMovementStateBehaviour* InBehaviour);
	void TickActiveBehaviours(float DeltaTime);
	bool ContainsBehaviour(TEnumAsByte<EMovementStateBehaviourKey> InKey);
	void SetBehaviourActive(TEnumAsByte<EMovementStateBehaviourKey> InKey, bool bInActiveState);
	template <typename TMovementStateBehaviour>
	TMovementStateBehaviour* GetBehaviour(TEnumAsByte<EMovementStateBehaviourKey> InKey);
	
private:
	UPROPERTY()
	TMap<TEnumAsByte<EMovementStateBehaviourKey>, UMovementStateBehaviour*> BehaviourMap;
	UPROPERTY()
	TArray<UMovementStateBehaviour*> Behaviours; 
	UPROPERTY()
	UMerinoMovementState* ParentState;
};

template <typename TMovementStateBehaviour>
TMovementStateBehaviour* UBehaviourController::GetBehaviour(TEnumAsByte<EMovementStateBehaviourKey> InKey)
{
	return static_cast<TMovementStateBehaviour*>(BehaviourMap[InKey]);
}
