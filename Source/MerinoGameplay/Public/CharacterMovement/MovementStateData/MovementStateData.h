// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterMovement/MovementStates/MerinoMovementState.h"
#include "Engine/DataAsset.h"

#include "MovementStateData.generated.h"
/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class MERINOGAMEPLAY_API UMovementStateData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EMerinoMovementStateKey> MovementStateKey;
};
