// Fill out your copyright notice in the Description page of Project Settings.
#include "IK\FootIKSolverComponent.h"
#include "MerinoDebugStatics.h"
#include "MerinoLogStatics.h"
#include "SkeletalMeshAttributes.h"
#include "CharacterMovement/MerinoMovementComponent.h"

// Sets default values for this component's properties
UFootIKSolverComponent::UFootIKSolverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
	CurrentFootPosition = FVector::Zero();
	NewFootPosition = FVector::Zero();
	BoneMap.Empty();
}

// Called when the game starts
void UFootIKSolverComponent::BeginPlay()
{
	Super::BeginPlay();
	SkeletalMeshComponent = GetOwner()->GetComponentByClass<USkeletalMeshComponent>();
	MovementComponent = GetOwner()->GetComponentByClass<UMerinoMovementComponent>();
	BoneMap.Add(EIKKEY::LeftFoot, LeftFootBone);
	BoneMap.Add(EIKKEY::RightFoot, RightFootBone);
}

void UFootIKSolverComponent::UpdateIKCalculations()
{
	FVector StepStart = GetOwner()->GetActorLocation() + MovementComponent->Velocity.GetSafeNormal() * StepDistance;
	NewFootPosition = StepStart;
	//UMerinoDebugStatics::DrawSingleFrameDebugSphere(GetWorld(), NewFootPosition, 10.0f, FColor::Green);
	if (FVector::Dist(NewFootPosition, CurrentFootPosition) > MinDistanceRecalculateFootPosition)
	{
		CurrentFootPosition = NewFootPosition;
	}
	//UMerinoDebugStatics::DrawSingleFrameDebugSphere(GetWorld(), CurrentFootPosition, 10.0f, FColor::Red);

	FVector CheckGroundLineTrace = -GetOwner()->GetActorUpVector() * IKCheckDistance;
	FVector RightLineTraceOrigin = CurrentFootPosition + GetOwner()->GetActorRightVector() * StepXOffset;
	FVector LeftLineTraceOrigin = CurrentFootPosition + -GetOwner()->GetActorRightVector() * StepXOffset;
	FHitResult RightHitResult;
	bool bRightHit = GetWorld()->LineTraceSingleByChannel(RightHitResult, RightLineTraceOrigin, RightLineTraceOrigin + CheckGroundLineTrace, ECC_WorldStatic);
	FHitResult LeftHitResult;
	bool bLeftHit = GetWorld()->LineTraceSingleByChannel(LeftHitResult, LeftLineTraceOrigin, LeftLineTraceOrigin + CheckGroundLineTrace, ECC_WorldStatic);
	if (bRightHit)
	{
		//UMerinoDebugStatics::DrawSingleFrameDebugSphere(GetWorld(), RightHitResult.ImpactPoint, 10.0f, FColor::Green);
	}
	if (bLeftHit)
	{
		//UMerinoDebugStatics::DrawSingleFrameDebugSphere(GetWorld(), LeftHitResult.ImpactPoint, 10.0f, FColor::Green);
	}
}


// Called every frame
void UFootIKSolverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

FVector UFootIKSolverComponent::GetEffectorJointPosition(TEnumAsByte<EIKKEY> Key) const
{
	if (BoneMap.Contains(Key) == false
		|| SkeletalMeshComponent == nullptr)
	{
		return FVector::Zero();
	}
	FVector InitialFootPosition = SkeletalMeshComponent->GetSocketLocation(BoneMap[Key].EffectorBoneName);	
	FVector CorrectedFootPosition = GetEffectorJointPosition(InitialFootPosition + GetOwner()->GetActorUpVector() * 20.0f);
	if (CorrectedFootPosition == FVector::Zero())
	{
		CorrectedFootPosition = InitialFootPosition;
	}
	return CorrectedFootPosition;
}

FVector UFootIKSolverComponent::GetEffectorJointPosition(FVector CheckGroundLineTraceStart) const
{
	FVector FootPosition = FVector::Zero();
	FHitResult HitResult;
	FVector CheckGroundLineTrace = -GetOwner()->GetActorUpVector() * IKCheckDistance;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, CheckGroundLineTraceStart, CheckGroundLineTraceStart + GetOwner()->GetActorUpVector() * 20.0f + CheckGroundLineTrace, ECC_WorldStatic);
	if (bHit)
	{
		FootPosition = HitResult.ImpactPoint;
		UMerinoDebugStatics::DrawSingleFrameDebugSphere(GetWorld(), FootPosition, 10.0f, FColor::Red);
	}
	return FootPosition;
}

