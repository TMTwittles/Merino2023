// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MerinoMovementState.generated.h"

class UMerinoMovementComponent;

UCLASS(Abstract)
class MERINOGAMEPLAY_API UMerinoMovementState : public UObject
{
	GENERATED_BODY()
public:
	UMerinoMovementState();
	UMerinoMovementState(UMerinoMovementComponent* _PawnMovementComponent);
	void ConfigureMovementState(UMerinoMovementComponent* _MovementComponent);
	virtual void Tick(float DeltaTime);
	void EnterMovementState();
	
protected:
	UMerinoMovementComponent* MovementComponent;
	virtual void OnEnter();
};
