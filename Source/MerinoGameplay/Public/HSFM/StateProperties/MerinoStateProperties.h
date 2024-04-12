// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "MerinoStateProperties.generated.h"

enum EMerinoStateID : int;
class UDataTable;

/**
 * 
 */
UCLASS()
class MERINOGAMEPLAY_API UMerinoStateProperties : public UObject
{
	GENERATED_BODY()
	
public:
	void Initialize(TEnumAsByte<EMerinoStateID> InStateID);
	float GetFloatProperty(FString PropertyKey);
	void AddFloatProperty(FString PropertyKey, float PropertyValue);
	bool ContainsFloatProperty(FString PropertyKey);
	TEnumAsByte<EMerinoStateID> GetStateID();
private:
	UPROPERTY()
	TEnumAsByte<EMerinoStateID> StateID;
	UPROPERTY()
	TMap<FString, float> FloatProperties;
};
