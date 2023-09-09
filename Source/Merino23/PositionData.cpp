// Fill out your copyright notice in the Description page of Project Settings.
#include "PositionData.h"

void UPositionData::AddPosition(FVector Position)
{
	bool AddPosition = true;
	for (FVector ExistingPosition : Positions)
	{
		if (AddPosition && FVector::Distance(ExistingPosition, Position) < MinPositionDistance)
		{
			AddPosition = false;
		}
	}

	if (AddPosition)
	{
		Positions.Add(Position);	
	}
}

void UPositionData::AddPosition(FNavLocation Location)
{
	bool AddPosition = true;
	for (FVector ExistingPosition : Positions)
	{
		if (AddPosition && FVector::Distance(ExistingPosition, Location.Location) < MinPositionDistance)
		{
			AddPosition = false;
		}
	}

	if (AddPosition)
	{
		NavLocations.Add(Location);
		Positions.Add(Location.Location);	
	}
}

void UPositionData::ClearPositions()
{
	Positions.Empty();
}
