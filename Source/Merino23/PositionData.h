// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PositionData.generated.h"

struct FNavLocation;

UCLASS(BlueprintType)
class MERINO23_API UPositionData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> Positions;
	
	TArray<FNavLocation> NavLocations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinPositionDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumStepsGeneratePositions;
	
	UFUNCTION(BlueprintCallable)
	void AddPosition(FVector Position);
	
	void AddPosition(FNavLocation Location);

	UFUNCTION(BlueprintCallable)
	void ClearPositions();
};
