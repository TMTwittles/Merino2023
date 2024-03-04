// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CharacterVelocityHandler.generated.h"

/**
 * 
 */
UCLASS()
class MERINOGAMEPLAY_API UCharacterVelocityHandler : public UObject
{
	GENERATED_BODY()

public:
	void TickVelocity();

private:
	
};
