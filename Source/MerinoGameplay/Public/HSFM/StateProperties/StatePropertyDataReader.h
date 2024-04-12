// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "StatePropertyDataReader.generated.h"

enum EMerinoStateID : int;
class UMerinoStateProperties;
struct FStatePropertyEntry;

/**
 * 
 */
UCLASS()
class MERINOGAMEPLAY_API UStatePropertyDataReader : public UObject
{
	GENERATED_BODY()
	
public:
	static void ReadFromGlobalStateProperties(const UDataTable* GlobalStatePropertiesDataTable, UMerinoStateProperties* StateProperties);

private:
	static bool TryReadAndAddPropertyValue(const FStatePropertyEntry* Entry, UMerinoStateProperties* StateProperties);
	static bool TryReadFloatValue(const FString* Value, float* ValueToFloat);
};
