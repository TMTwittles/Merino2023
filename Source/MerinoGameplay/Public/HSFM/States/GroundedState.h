// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "MovementState.h"
#include "GroundedState.generated.h"

class UMerinoMovementComponent;
/**
 * 
 */
UCLASS()
class MERINOGAMEPLAY_API UGroundedState : public UMovementState
{
	GENERATED_BODY()
	
public:
	virtual void TickState(float DeltaTime) override;
};
