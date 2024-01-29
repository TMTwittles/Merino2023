// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "MerinoMovementState.generated.h"

class UMovementStateControllerComponent;
class UMovementStateData;
enum EMerinoMovementStateKey : int;
class UMerinoMovementComponent;

UCLASS(BlueprintType, Abstract)
class MERINOGAMEPLAY_API UMerinoMovementState : public UObject
{
	GENERATED_BODY()
public:
	UMerinoMovementState();
	void ConfigureMovementState(UMovementStateControllerComponent* _MSController, UMovementStateData* _Data, UMerinoMovementComponent* _MovementComponent, UWorld* _World);
	virtual void Tick(float DeltaTime);
	void EnterMovementState();
	
protected:
	virtual void OnEnter();
	virtual void PostConfigure(UMovementStateData* Data);

protected:
	UPROPERTY()
	UMovementStateControllerComponent* Controller;
	UPROPERTY()
	UMerinoMovementComponent* MovementComponent;
	UPROPERTY()
	UWorld* World;
};
