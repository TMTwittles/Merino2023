#pragma once
#include "MerinoMovementStateKey.generated.h"

UENUM(BlueprintType)
enum EStateID
{
	Grounded UMETA(DisplayName = "Grounded"),
	Falling__ UMETA(DisplayName = "Falling__"),
	Jumping__ UMETA(DisplayName = "Jumping__"),
	Strafing__ UMETA(DisplayName = "Strafing__")
};
