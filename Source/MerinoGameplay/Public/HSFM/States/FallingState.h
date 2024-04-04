// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HSFM/States/MerinoState.h"
#include "FallingState.generated.h"

class UMerinoMovementComponent;
/**
 * 
 */
UCLASS()
class MERINOGAMEPLAY_API UFallingState : public UMerinoState
{
	GENERATED_BODY()

public:
	virtual void TickState(float DeltaTime);
	
private:
	UPROPERTY()
	TObjectPtr<UMerinoMovementComponent> MovementComponent;
};
