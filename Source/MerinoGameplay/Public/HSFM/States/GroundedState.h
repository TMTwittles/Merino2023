// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MerinoState.h"
#include "GroundedState.generated.h"

class UMerinoMovementComponent;
/**
 * 
 */
UCLASS()
class MERINOGAMEPLAY_API UGroundedState : public UMerinoState
{
	GENERATED_BODY()
	
public:
	~UGroundedState() override;
	virtual void TickState(float DeltaTime) override;

protected:
	virtual void PostInitialise(AActor* Owner) override;

private:
	UMerinoMovementComponent* MovementComponent;
};
