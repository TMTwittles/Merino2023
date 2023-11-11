// Fill out your copyright notice in the Description page of Project Settings.


#include "MerinoDebugStatics.h"

void UMerinoDebugStatics::DrawNonPersistentDebugLine(UWorld* World, FVector Start, FVector End, FColor Color)
{
	DrawDebugLine(World, Start, End, Color, false, -1, 0, 1.0f);
}
