#pragma once

#include "Engine/DataTable.h"
#include "Position.generated.h"

USTRUCT(BlueprintType)
struct MERINO23_API FPosition : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	void AddPosition(FVector _PositionVector);

	UPROPERTY(BlueprintReadWrite)
	TArray<FVector> Positions;
	
};
