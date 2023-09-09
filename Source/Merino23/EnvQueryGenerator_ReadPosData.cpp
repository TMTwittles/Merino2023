// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvQueryGenerator_ReadPosData.h"

#include "PositionData.h"

void UEnvQueryGenerator_ReadPosData::GenerateItems(FEnvQueryInstance& QueryInstance) const
{
	if (PositionData == nullptr)
	{
		UE_LOG(LogClass, Warning, TEXT("ERROR: Position data is null, unable to read pos data."))
		return;
	}

	TArray<FNavLocation> NavLocations;
	for (FNavLocation Location : PositionData->NavLocations)
	{
		NavLocations.Add(Location);
	}
	ProjectAndFilterNavPoints(NavLocations, QueryInstance);
	StoreNavPoints(NavLocations, QueryInstance);
}
