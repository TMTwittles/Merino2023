// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/Generators/EnvQueryGenerator_ProjectedPoints.h"
#include "EnvQueryGenerator_ReadPosData.generated.h"

class UPositionData;

UCLASS()
class MERINO23_API UEnvQueryGenerator_ReadPosData : public UEnvQueryGenerator_ProjectedPoints
{
	GENERATED_BODY()
	
	virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;

public:
	UPROPERTY(EditAnywhere)
	UPositionData* PositionData;
};
