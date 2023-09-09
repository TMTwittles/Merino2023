// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PositionData.h"
#include "PositionGenerator.generated.h"

class UPositionData;
class UDataTable;
struct FPosition;
struct FPositionGenConfig;
struct FNavLocation;
class ARecastNavMesh;

UCLASS(BlueprintType)
class MERINO23_API UPositionGenerator : public UObject
{
	GENERATED_BODY()
	
public:
	UPositionGenerator();
	
	UFUNCTION(BlueprintCallable)
	void GeneratePositions(UWorld* World, UPositionData* PositionData);

private:
	void ExtractTileVertices(const int NavmeshTileID, const ARecastNavMesh* RecastNavMesh, TArray<FNavLocation>& TileVertices);
	void GenPositionsFromVertices(TArray<FNavLocation> Vertices, TArray<FNavLocation>& GeneratedPositions);
	
	UPositionData* Data;
};
