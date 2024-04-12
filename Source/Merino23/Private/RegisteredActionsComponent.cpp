// Fill out your copyright notice in the Description page of Project Settings.
#include "RegisteredActionsComponent.h"
#include "RegisteredActionID.h"
#include "MerinoLogStatics.h"

URegisteredActionsComponent::URegisteredActionsComponent()
{
}

void URegisteredActionsComponent::BeginPlay()
{
	// Create entries for the actions that the component will register.
	for (ERegisteredActionID ActionIDToRegister : ActionsToRegister)
	{
		if (RegisteredActionsMap.Contains(ActionIDToRegister))
		{
			UMerinoLogStatics::LogError(TEXT("Error: Action {0} already registered. Please ensure no duplicate entries"),
				{ UEnum::GetValueAsString((ActionIDToRegister)) });
		}
		RegisteredActionsMap.Add(ActionIDToRegister, -1);
	}
}

void URegisteredActionsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ClearRegisteredActions();
}

void URegisteredActionsComponent::RegisterAction(ERegisteredActionID ActionID)
{
	if (RegisteredActionsMap.Contains(ActionID) == false)
	{
		UMerinoLogStatics::LogError(TEXT("Error: No entry for {0}, unable to register action."),
			{ UEnum::GetValueAsString(ActionID) });
		return;
	}

	// TODO: We are currently making it worth 1, so this action is registered for 1 frame. 
	// Make this clearer in code, remove magic numbers and add option to make value registered for longer. 
	RegisteredActionsMap[ActionID] = 1;
}

bool URegisteredActionsComponent::ActionRegistered(ERegisteredActionID ActionID)
{
	bool bActionRegistered = false;
	if (RegisteredActionsMap.Contains(ActionID) == false)
	{
		UMerinoLogStatics::LogError(TEXT("Error: No entry for {0}, unable to determine if registered"),
		{UEnum::GetValueAsString(ActionID)});
	}
	else
	{
		// TODO: Make this clearer as to what negative one means.
		bActionRegistered = RegisteredActionsMap[ActionID] > -1;
	}
	return bActionRegistered;
}

void URegisteredActionsComponent::ClearRegisteredActions()
{
	for (ERegisteredActionID RegisteredActionID : ActionsToRegister)
	{
		int ActionValue = RegisteredActionsMap[RegisteredActionID];
		ActionValue = FMath::Clamp(ActionValue - 1, -1, ActionValue);
		RegisteredActionsMap[RegisteredActionID] = ActionValue;
	}
}


