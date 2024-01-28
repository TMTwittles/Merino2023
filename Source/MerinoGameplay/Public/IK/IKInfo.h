#pragma once
#include "IKBone.h"
#include "IKInfo.generated.h"

USTRUCT(BlueprintType)
struct FIKInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EIKBone> BoneKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName EffectorBoneName;
};
