// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HSFM/MerinoStateID.h"
#include "TransitionData.generated.h"

class UMerinoState;
class UTransitionRule;
/**
 * 
 */
UCLASS()
class MERINOGAMEPLAY_API UTransitionData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UTransitionRule>> TransitionRules;
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EMerinoStateID> TransitionStateID;
};
