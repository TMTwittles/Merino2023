// Fill out your copyright notice in the Description page of Project Settings.
#include "HSFM/StateProperties/MerinoStateProperties.h"
#include "HSFM/StateProperties/StatePropertyDataReader.h"
#include "MerinoStatics/Public/MerinoLogStatics.h"

void UMerinoStateProperties::Initialize(TEnumAsByte<EMerinoStateID> InStateID)
{
	StateID = InStateID;
}

float UMerinoStateProperties::GetFloatProperty(FString PropertyKey)
{
	float FloatProperty = -1.0f;
	// TODO: Output error if property name is not contained here. 
	if (FloatProperties.Contains(PropertyKey))
	{
		FloatProperty = FloatProperties[PropertyKey];
	}
	else
	{
		UMerinoLogStatics::LogError(
			TEXT("Unable to locate float property with key: {0} for state: {1}"), 
			{PropertyKey, 
			UEnum::GetValueAsString(StateID.GetValue())});
	}
	return FloatProperty;
}

void UMerinoStateProperties::AddFloatProperty(FString PropertyKey, float PropertyValue)
{
	FloatProperties.Add(PropertyKey, PropertyValue);
}

bool UMerinoStateProperties::ContainsFloatProperty(FString PropertyKey)
{
	return FloatProperties.Contains(PropertyKey);
}

TEnumAsByte<EMerinoStateID> UMerinoStateProperties::GetStateID()
{
	return StateID;
}
