#pragma once
#include "MerinoStateID.generated.h"

UENUM(BlueprintType)
enum EMerinoStateID
{
	Ground UMETA(DisplayName = "Grounded"),
	Falling UMETA(DisplayName = "Falling"),
	Jumping UMETA(DisplayName = "Jumping")
};
