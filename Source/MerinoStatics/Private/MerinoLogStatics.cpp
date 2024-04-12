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

void UMerinoLogStatics::LogMessage(const TCHAR* InString, const FStringFormatOrderedArguments& InMessageArgs)
{
	FString OutputMessage;
	if (InMessageArgs.Num() == 0)
	{
		OutputMessage = InString;
	}
	else
	{
		OutputMessage = FString::Format(InString, InMessageArgs);
	}
	UE_LOG(LogTemp, Log, TEXT("%s"), *OutputMessage);
}

void UMerinoLogStatics::LogError(const TCHAR* InErrorString, const FStringFormatOrderedArguments& InErrorMessageArgs)
{
	FString OutputErrorMessage;
	if (InErrorMessageArgs.Num() == 0)
	{
		OutputErrorMessage = InErrorString;
	}
	else
	{
		OutputErrorMessage = FString::Format(InErrorString, InErrorMessageArgs);
	}
	UE_LOG(LogTemp, Error, TEXT("%s"), *OutputErrorMessage);
}
