// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "TransitionData.h"
#include "Engine/DataAsset.h"
#include "HSFM/MerinoStateID.h"
#include "HSFM/States/MerinoState.h"
#include "StateData.generated.h"

/**
 * 
 */
UCLASS()
class MERINOGAMEPLAY_API UStateData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FName StateName;
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EMerinoStateID> StateID;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMerinoState> State;
	UPROPERTY(EditAnywhere)
	TArray<UTransitionData*> Transitions;
};
