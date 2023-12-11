// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "AirMovementStateData.h"
#include "JumpingMovementStateData.generated.h"

/**
 * 
 */
UCLASS()
class MERINOGAMEPLAY_API UJumpingMovementStateData : public UAirMovementStateData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float JumpForce;
};
