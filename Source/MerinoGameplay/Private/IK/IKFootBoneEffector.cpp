// Fill out your copyright notice in the Description page of Project Settings.
#include "IK/IKFootBoneEffector.h"

#include "MerinoDebugStatics.h"
#include "IK/IKState.h"

UIKFootBoneEffector::UIKFootBoneEffector()
{
}

void UIKFootBoneEffector::Initialize(UWorld* InWorld, USkeletalMeshComponent* InSkeletalMeshComponent, FName InBoneName,
	float InEnterIKAlphaSpeed, float InReleaseIKAlphaSpeed, float InIKCheckDistance, float InFootPositionAdjustmentAmount)
{
	World = InWorld;
	SkeletalMeshComponent = InSkeletalMeshComponent;
	BoneName = InBoneName;
	EnterIKAlphaSpeed = InEnterIKAlphaSpeed;
	ReleaseIKAlphaSpeed = InReleaseIKAlphaSpeed;
	IKCheckDistance = InIKCheckDistance;
	FootPositionAdjustmentAmount = InFootPositionAdjustmentAmount;
	CurrentState = Inactive;
	EffectorLocation = FVector::Zero();
	ElapsedIKAlpaTickTime = 0.0f;
}

void UIKFootBoneEffector::Ground()
{
	CurrentState = EnteringActive;
	EffectorLocation = CalculateEffectorLocation();
}

void UIKFootBoneEffector::Release()
{
	CurrentState = EnteringInactive;
}

void UIKFootBoneEffector::Tick(float DeltaTime)
{
	if (CurrentState == EnteringActive)
	{
		TickUpdateIK(DeltaTime, 0.0f, 1.0f, EnterIKAlphaSpeed, Active);
	}
	else if (CurrentState == EnteringInactive)
	{
		TickUpdateIK(DeltaTime, 1.0f, 0.0f, ReleaseIKAlphaSpeed, Inactive);
	}
}

FVector UIKFootBoneEffector::GetEffectorLocation()
{
	return EffectorLocation;
}

float UIKFootBoneEffector::GetIKAlpha()
{
	return IKAlpha;
}


FVector UIKFootBoneEffector::CalculateEffectorLocation()
{
	FVector FootPosition = FVector::Zero();
	FHitResult HitResult;
	FVector CheckGroundLineTraceStart = SkeletalMeshComponent->GetSocketLocation(BoneName) + SkeletalMeshComponent->GetOwner()->GetActorUpVector() * 20.0f;
	FVector CheckGroundLineTrace = -SkeletalMeshComponent->GetOwner()->GetActorUpVector() * IKCheckDistance;
	bool bHit = World->LineTraceSingleByChannel(HitResult, CheckGroundLineTraceStart, CheckGroundLineTraceStart + CheckGroundLineTrace, ECC_WorldStatic);
	if (bHit)
	{
		FootPosition = HitResult.ImpactPoint + HitResult.ImpactNormal * FootPositionAdjustmentAmount;
		
	}
	return FootPosition;
}

void UIKFootBoneEffector::TickUpdateIK(float DeltaTime, float StartAlpha, float EndAlpha, float UpdateAlphaSpeed, EIKState TargetState)
{
	float LerpAlpha = 0.0f;
	if (ElapsedIKAlpaTickTime != 0.0f)
	{
		LerpAlpha = ElapsedIKAlpaTickTime / UpdateAlphaSpeed;
	}
	float Function = LerpAlpha * LerpAlpha * LerpAlpha;
	IKAlpha = FMath::Lerp(StartAlpha, EndAlpha, Function);
	ElapsedIKAlpaTickTime += DeltaTime;
	if (IKAlpha >= EndAlpha)
	{
		CurrentState = TargetState;
		IKAlpha = EndAlpha;
		ElapsedIKAlpaTickTime = 0.0f;
	}
}
