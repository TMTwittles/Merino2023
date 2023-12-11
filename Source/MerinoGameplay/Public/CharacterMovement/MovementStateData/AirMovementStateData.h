// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovementStateData.h"
#include "AirMovementStateData.generated.h"

/**
 * 
 */
UCLASS()
class MERINOGAMEPLAY_API UAirMovementStateData : public UMovementStateData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	float Gravity;

	UPROPERTY(EditAnywhere)
	float AirControlAcceleration;

	UPROPERTY(EditAnywhere)
	float AirControlDeceleration;
	
	UPROPERTY(EditAnywhere)
	float MaxAirControlSpeed;
};
