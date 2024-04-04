// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "HSFM/States/MerinoState.h"
#include "JumpingState.generated.h"

class UMerinoMovementComponent;
/**
 * 
 */
UCLASS()
class MERINOGAMEPLAY_API UJumpingState : public UMerinoState
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	TObjectPtr<UMerinoMovementComponent> MovementComponent;
};
