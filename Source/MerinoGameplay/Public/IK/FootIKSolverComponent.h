// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "IKInfo.h"
#include "Components/ActorComponent.h"
#include "FootIKSolverComponent.generated.h"

enum IKBone : unsigned int;
class UMerinoMovementComponent;
class UIKFootBoneEffector;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MERINOGAMEPLAY_API UFootIKSolverComponent : public UActorComponent
{
private:
	GENERATED_BODY()

public:
	UFootIKSolverComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void GroundFoot(TEnumAsByte<EIKBone> Key);
	UFUNCTION(BlueprintCallable)
	void ReleaseFoot(TEnumAsByte<EIKBone> Key);
	void TickFootAlphas(float DeltaTime);
	UFUNCTION(BlueprintCallable)
	UIKFootBoneEffector* GetFootBoneEffector(TEnumAsByte<EIKBone> Key);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="True"), Category="IK Attributes")
	float IKCheckDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="True"), Category="IK Attributes")
	float StepDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="True"), Category="IK Attributes")
	float FeetPositionAdjustmentAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="True"), Category="IK Attributes")
	float GroundIKAlphaSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="True"), Category="IK Attributes")
	float ReleaseIKAlphaSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="True"), Category="Affected bones")
	FIKInfo LeftFootBone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="True"), Category="Affected bones")
	FIKInfo RightFootBone;
	
	UPROPERTY()
	TMap<TEnumAsByte<EIKBone>, UIKFootBoneEffector*> AffectedBones;
	UPROPERTY()
	USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY()
	UMerinoMovementComponent* MovementComponent;
	FVector CurrentFootPosition;
	FVector NewFootPosition;
};
