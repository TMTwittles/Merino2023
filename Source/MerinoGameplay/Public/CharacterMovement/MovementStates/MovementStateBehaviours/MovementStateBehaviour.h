// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "MovementStateBehaviour.generated.h"
class UMerinoMovementState;
/**
 * 
 */
UCLASS(BlueprintType, Abstract)
class MERINOGAMEPLAY_API UMovementStateBehaviour : public UObject
{
private:
	GENERATED_BODY()

public:
	void SetParentMovementState(UMerinoMovementState* InMovementState);
	virtual void TickBehaviour(float DeltaTime);
	void SetActive(bool bActiveState);
	bool Active();

protected:
	virtual void OnActive();
	virtual void OnInActive();

protected:
	UPROPERTY()
	UMerinoMovementState* MovementState;
	
private:
	bool bActive;
};
