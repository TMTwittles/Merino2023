// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "MerinoLogStatics.generated.h"

UCLASS()
class MERINOSTATICS_API UMerinoLogStatics : public UObject
{
	GENERATED_BODY()

public:
	static void LogVector(FString LogIdentifier, FVector VectorToLog);
	static void LogFloat(FString LogIdentifier, float FloatToLog);
	static void LogMessage(const TCHAR* InString, const FStringFormatOrderedArguments& InMessageArgs = {});
	static void LogError(const TCHAR* InErrorString, const FStringFormatOrderedArguments& InErrorMessageArgs = {});
};
