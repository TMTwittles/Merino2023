#pragma once

#include "IKInfo.generated.h"

USTRUCT(BlueprintType)
struct FIKInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName EffectorBoneName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TargetJointBoneName;
};
