// Fill out your copyright notice in the Description page of Project Settings.


#include "PositionGenerator.h"

#include "IndexIter.h"
#include "Merino23.h"
#include "MerinoMathStatics.h"
#include "PositionGenConfig.h"
#include "Position.h"
#include "AI/NavigationSystemBase.h"
#include "Engine/DataTable.h"
#include "NavMesh/RecastNavMesh.h"
#include "PositionData.h"
#include "Engine/Internal/Kismet/BlueprintTypeConversions.h"
#include "Navmesh/Public/Detour/DetourNavMesh.h"
#include "Navmesh/Public/Detour/DetourAlloc.h"

UPositionGenerator::UPositionGenerator()
{
}

void UPositionGenerator::GeneratePositions(UWorld* World, UPositionData* PositionData)
{
	Data = PositionData;
	if (PositionData == nullptr)
	{
		UE_LOG(LogClass, Error, TEXT("Error: Position generator configuration is null."));
		return;
	}
	
	const ARecastNavMesh* RecastNavMesh = static_cast<ARecastNavMesh*>(World->GetNavigationSystem()->GetMainNavData());
	if (RecastNavMesh == nullptr)
	{
		UE_LOG(LogClass, Error, TEXT("Error: Unable to locate navmesh. Please ensure navmesh has been placed in the scene."));
		return;
	}
	
	Data->ClearPositions();
	// Extract vertices from tiles.
	TArray<FNavLocation> GeneratedPositions;
	TArray<FNavPoly> Polys;
	int NumTiles = RecastNavMesh->TileNumberHardLimit;
	for (int TileIter = 0; TileIter < 5; TileIter++)
	{
		if (RecastNavMesh->GetPolysInTile(TileIter, Polys) && Polys.Num() == 0)
		{
			continue;
		}
		ExtractTileVertices(TileIter, RecastNavMesh, GeneratedPositions);
		for (int i = 0; i < Data->NumStepsGeneratePositions; i++)
		{
			GenPositionsFromVertices(GeneratedPositions, GeneratedPositions);		
		}
		for (FNavLocation GeneratedPosition : GeneratedPositions)
		{
			Data->AddPosition(GeneratedPosition);
		}
		GeneratedPositions.Empty();
	}
}

void UPositionGenerator::ExtractTileVertices(const int NavmeshTileID, const ARecastNavMesh* RecastNavMesh, TArray<FNavLocation>& TileVertices)
{
	TArray<FNavPoly> NavPolys;
	TArray<FVector> PolyVerts;
	RecastNavMesh->GetPolysInTile(NavmeshTileID, NavPolys);
	for (FNavPoly NavPoly : NavPolys)
	{
		RecastNavMesh->GetPolyVerts(NavPoly.Ref, PolyVerts);
		for (FVector Vert : PolyVerts)
		{
			TileVertices.Add(FNavLocation(Vert, NavPoly.Ref));
		}
	}
	if (TileVertices.Num() == 0)
	{
		UE_LOG(LogClass, Warning, TEXT("Unable to extract vertices from tile {%i}"), NavmeshTileID);
	}
}

void UPositionGenerator::GenPositionsFromVertices(TArray<FNavLocation> Vertices, TArray<FNavLocation>& GeneratedPositions)
{
	const int NumVectors = Vertices.Num();
	IndexIter Iter(NumVectors);
	for (int StartIter = 0; StartIter < NumVectors; StartIter++)
	{
		Iter.ReorderIndexQueue(StartIter);
		FNavLocation StartLocation = Vertices[Iter.GetNextIndex()];
		FVector P1 = StartLocation.Location;
		FVector P2 = Vertices[Iter.GetNextIndex()];
		FVector P3 = Vertices[Iter.GetNextIndex()];
		FVector CentroidPosition = UMerinoMathStatics::CalculateCentroid(P1, P2, P3);
		GeneratedPositions.Add(FNavLocation(CentroidPosition, StartLocation.NodeRef));
	}
}
