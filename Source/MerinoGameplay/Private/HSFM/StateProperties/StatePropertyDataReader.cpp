// Fill out your copyright notice in the Description page of Project Settings.
#include "HSFM/StateProperties/StatePropertyDataReader.h"
#include "HSFM/StateProperties/StatePropertyType.h"
#include "HSFM/StateProperties/StatePropertyEntry.h"
#include "HSFM/StateProperties/MerinoStateProperties.h"
#include "MerinoStatics/Public/MerinoLogStatics.h"

void UStatePropertyDataReader::ReadFromGlobalStateProperties(const UDataTable* GlobalStatePropertiesDataTable, UMerinoStateProperties* StateProperties)
{
	TArray<FStatePropertyEntry*> PropertyEntries;
	FString ContextString = "Write something informative here";
	GlobalStatePropertiesDataTable->GetAllRows(ContextString, PropertyEntries);
	for (FStatePropertyEntry* PropertyEntry : PropertyEntries)
	{
		if (PropertyEntry->bAffectsAllStates 
			|| PropertyEntry->SharedStates.Contains(StateProperties->GetStateID()))
		{
			UStatePropertyDataReader::TryReadAndAddPropertyValue(PropertyEntry, StateProperties);
		}
	}
}

bool UStatePropertyDataReader::TryReadAndAddPropertyValue(const FStatePropertyEntry* Entry, UMerinoStateProperties* StateProperties)
{
	bool bReadAndAddedProperty = false;
	FString PropertyKey = Entry->PropertyKey;
	switch (Entry->PropertyType)
	{
		case FloatStatePropertyType:
			float ValueToFloat = -1.0f;
			if (StateProperties->ContainsFloatProperty(PropertyKey))
			{
				UMerinoLogStatics::LogError(
					TEXT("Error: State: {0} already contains a float property for {1}."),
					{ UEnum::GetValueAsString(StateProperties->GetStateID().GetValue()), PropertyKey });
				return bReadAndAddedProperty;
			}
			if (UStatePropertyDataReader::TryReadFloatValue(&Entry->PropertyValue, &ValueToFloat) == false)
			{
				UMerinoLogStatics::LogError(
					TEXT("Error: Cannot convert property: {0} to float with value: {1} for state: {2}."),
					{ PropertyKey, Entry->PropertyValue, UEnum::GetValueAsString(StateProperties->GetStateID().GetValue()) });
				return bReadAndAddedProperty;
			}
			StateProperties->AddFloatProperty(PropertyKey, ValueToFloat);
			bReadAndAddedProperty = true;
	}
	return bReadAndAddedProperty;
}

bool UStatePropertyDataReader::TryReadFloatValue(const FString* Value, float* OutValueToFloat)
{
	bool bReadFloatValue = false;
	if (FCString::IsNumeric(**Value))
	{
		*OutValueToFloat = FCString::Atof(**Value);
		bReadFloatValue = true;
	}
	return bReadFloatValue;
}
