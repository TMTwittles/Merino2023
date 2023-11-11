// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MerinoMovementState.h"
#include "FallingMovementState.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MERINOGAMEPLAY_API UFallingMovementState : public UMerinoMovementState
{
public:
	UFallingMovementState();
	virtual void Tick(float DeltaTime) override;

private:
	GENERATED_BODY()
};
