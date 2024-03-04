#pragma once
#include "MerinoMovementStateKey.generated.h"

UENUM(BlueprintType)
enum EStateID
{
	Grounded UMETA(DisplayName = "Grounded"),
	Falling UMETA(DisplayName = "Falling"),
	Jumping UMETA(DisplayName = "Jumping"),
	Strafing UMETA(DisplayName = "Strafing")
};
