// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MovementStateControllerComponent.generated.h"

class UMerinoMovementComponent;
class UMovementStateData;
enum EMerinoMovementStateKey : int;
class UMerinoMovementState;

UCLASS(meta=(BlueprintSpawnableComponent))
class MERINOGAMEPLAY_API UMovementStateControllerComponent : public UActorComponent
{
private:
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;
	void Configure();
	void SetActiveMovementState(EMerinoMovementStateKey NewActiveMovementStateKey);

private:
	UMerinoMovementState* BuildMovementState(UMovementStateData* Data) const;
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess))
	TArray<UMovementStateData*> MovementStates;
	UPROPERTY()
	TMap<TEnumAsByte<EMerinoMovementStateKey>, UMerinoMovementState*> MovementStateMap;
	UPROPERTY()
	UMerinoMovementState* ActiveMovementState;
};
