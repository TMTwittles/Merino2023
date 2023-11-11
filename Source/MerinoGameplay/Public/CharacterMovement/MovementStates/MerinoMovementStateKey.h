﻿#pragma once
#include "MerinoMovementStateKey.generated.h"

UENUM(BlueprintType)
enum EMerinoMovementStateKey
{
	Grounded UMETA(DisplayName = "Grounded"),
	Falling UMETA(DisplayName = "Falling"),
	Jumping UMETA(DisplayName = "Jumping")
};