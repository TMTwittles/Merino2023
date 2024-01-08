// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "IKInfo.h"
#include "IKKEY.h"
#include "Components/ActorComponent.h"
#include "FootIKSolverComponent.generated.h"

class UMerinoMovementComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MERINOGAMEPLAY_API UFootIKSolverComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFootIKSolverComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FVector GetEffectorJointPosition(TEnumAsByte<EIKKEY> Key) const;
	
protected:
	virtual void BeginPlay() override;

private:
	void UpdateIKCalculations();
	FVector GetEffectorJointPosition(FVector CheckGroundLineTraceStart) const;

public:
	
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="True"), Category="IK Attributes")
	float IKCheckDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="True"), Category="IK Attributes")
	float StepDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="True"), Category="IK Attributes")
	float StepXOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="True"), Category="IK Attributes")
	float MinDistanceRecalculateFootPosition;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="True"), Category="Affected bones")
	FIKInfo LeftFootBone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="True"), Category="Affected bones")
	FIKInfo RightFootBone;
	
	TMap<TEnumAsByte<EIKKEY>, FIKInfo> BoneMap;
	USkeletalMeshComponent* SkeletalMeshComponent;
	UMerinoMovementComponent* MovementComponent;
	FVector CurrentFootPosition;
	FVector NewFootPosition;
};
