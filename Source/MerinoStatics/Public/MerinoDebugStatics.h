// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MerinoDebugStatics.generated.h"

/**
 * 
 */
UCLASS()
class MERINOSTATICS_API UMerinoDebugStatics : public UObject
{
	GENERATED_BODY()

public:
	static void DrawNonPersistentDebugLine(UWorld* World, FVector Start, FVector End, FColor Color);
};
