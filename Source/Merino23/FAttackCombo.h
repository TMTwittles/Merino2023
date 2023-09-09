#pragma once
#include "Engine/DataTable.h"
#include "FAttackCombo.generated.h"

USTRUCT(BlueprintType)
struct FAttackCombo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* AttackAnimMontage;
};
