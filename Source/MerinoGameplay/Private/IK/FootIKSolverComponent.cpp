// Fill out your copyright notice in the Description page of Project Settings.
#include "IK\FootIKSolverComponent.h"
#include "CharacterMovement/MerinoMovementComponent.h"
#include "IK/IKBone.h"
#include "IK/IKFootBoneEffector.h"

// Sets default values for this component's properties
UFootIKSolverComponent::UFootIKSolverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	CurrentFootPosition = FVector::Zero();
	NewFootPosition = FVector::Zero();
	AffectedBones.Empty();
}

void UFootIKSolverComponent::BeginPlay()
{
	Super::BeginPlay();

	SkeletalMeshComponent = GetOwner()->GetComponentByClass<USkeletalMeshComponent>();
	MovementComponent = GetOwner()->GetComponentByClass<UMerinoMovementComponent>();
	UIKFootBoneEffector* LeftFootBoneEffector = NewObject<UIKFootBoneEffector>();
	LeftFootBoneEffector->Initialize(GetWorld(), SkeletalMeshComponent, LeftFootBone.EffectorBoneName,
		GroundIKAlphaSpeed, ReleaseIKAlphaSpeed, IKCheckDistance, FeetPositionAdjustmentAmount);
	UIKFootBoneEffector* RightFootBoneEffector = NewObject<UIKFootBoneEffector>();
	RightFootBoneEffector->Initialize(GetWorld(), SkeletalMeshComponent, RightFootBone.EffectorBoneName,
		GroundIKAlphaSpeed, ReleaseIKAlphaSpeed, IKCheckDistance, FeetPositionAdjustmentAmount);
	AffectedBones.Add(LeftFoot, LeftFootBoneEffector);
	AffectedBones.Add(RightFoot, RightFootBoneEffector);
}

// Called every frame
void UFootIKSolverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TickFootAlphas(DeltaTime);
}


void UFootIKSolverComponent::GroundFoot(TEnumAsByte<EIKBone> Key)
{
	if (AffectedBones.Contains(Key) == false)
	{
		return;
	}
	AffectedBones[Key]->Ground();
}

void UFootIKSolverComponent::ReleaseFoot(TEnumAsByte<EIKBone> Key)
{
	if (AffectedBones.Contains(Key) == false)
	{
		return;
	}
	AffectedBones[Key]->Release();
}

void UFootIKSolverComponent::TickFootAlphas(float DeltaTime)
{
	if (AffectedBones.Num() == 0)
	{
		return;
	}

	AffectedBones[LeftFoot]->Tick(DeltaTime);
	AffectedBones[RightFoot]->Tick(DeltaTime);
}

UIKFootBoneEffector* UFootIKSolverComponent::GetFootBoneEffector(TEnumAsByte<EIKBone> Key)
{
	if (AffectedBones.Contains(Key) == false)
	{
		return nullptr;
	}
	return AffectedBones[Key];
}

