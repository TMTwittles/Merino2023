// Fill out your copyright notice in the Description page of Project Settings.


#include "MerinoLogStatics.h"

void UMerinoLogStatics::LogVector(FString LogIdentifier, FVector VectorToLog)
{
	UE_LOG(LogTemp, Log, TEXT("%s Logging vector: %s"), *LogIdentifier, *VectorToLog.ToString());
}

void UMerinoLogStatics::LogFloat(FString LogIdentifier, float FloatToLog)
{
	UE_LOG(LogTemp, Log, TEXT("%s: %f"), *LogIdentifier, FloatToLog)
}

void UMerinoLogStatics::LogError(const TCHAR* InErrorString,const FStringFormatOrderedArguments& InErrorMessageArgs)
{
	FString OutputErrorMessage = FString::Format(InErrorString, InErrorMessageArgs);
	UE_LOG(LogTemp, Error, TEXT("%s"), *OutputErrorMessage);
}
