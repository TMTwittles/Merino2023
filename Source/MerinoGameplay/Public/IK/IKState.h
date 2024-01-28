#pragma once
#include "IKState.generated.h"

UENUM(BlueprintType)
enum EIKState
{
	Inactive UMETA(DisplayName = "Inactive"),
	EnteringActive UMETA(DisplayName = "EnteringActive"),
	Active UMETA(DisplayName = "Active"),
	EnteringInactive UMETA(DisplayName = "EnteringInactive")
};
