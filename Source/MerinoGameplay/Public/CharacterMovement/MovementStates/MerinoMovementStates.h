#pragma once
#include "MerinoMovementStates.generated.h"

UENUM(BlueprintType)
enum EMerinoMovementStates
{
	Grounded UMETA(DisplayName = "Grounded"),
	Falling UMETA(DisplayName = "Falling")
};
