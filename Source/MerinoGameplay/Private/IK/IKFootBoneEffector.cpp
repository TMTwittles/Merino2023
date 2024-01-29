// Fill out your copyright notice in the Description page of Project Settings.
#include "IK/IKFootBoneEffector.h"

#include "MerinoDebugStatics.h"
#include "MerinoLogStatics.h"
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
	if (CurrentState != Inactive)
	{
		IKAlpha = 0.0f;
	}
	
	ElapsedIKAlpaTickTime = 0.0f;
	CurrentState = EnteringActive;
	EffectorLocation = CalculateEffectorLocation();
}

void UIKFootBoneEffector::Release()
{
	if (CurrentState != Active)
	{
		IKAlpha = 1.0f;
	}
	
	ElapsedIKAlpaTickTime = 0.0f;
	CurrentState = EnteringInactive;
}

void UIKFootBoneEffector::Tick(float DeltaTime)
{
	if (CurrentState == EnteringActive)
	{
		//UMerinoLogStatics::LogFloat("Entering active: ", IKAlpha);
		TickEnterActiveIK(DeltaTime);
	}
	else if (CurrentState == EnteringInactive)
	{
		UMerinoLogStatics::LogFloat("Entering inactive: ", IKAlpha);
		TickEnterReleaseIK(DeltaTime);
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
		UMerinoDebugStatics::DrawDebugSphereForDuration(World, FootPosition, 10.0f, FColor::Red, 10.0f);
	}
	return FootPosition;
}

float UIKFootBoneEffector::GetTickIKAlphaValue(float DeltaTime, float Speed) const
{
	return FMath::Lerp(0.0f, 1.0f, Speed * DeltaTime);
}

void UIKFootBoneEffector::TickEnterActiveIK(float DeltaTime)
{
	IKAlpha += GetTickIKAlphaValue(DeltaTime, EnterIKAlphaSpeed);
	UMerinoLogStatics::LogFloat("Ground IK Alpha: ", IKAlpha);
	if (IKAlpha >= 1.0f)
	{
		CurrentState = Active;
		IKAlpha = 1.0f;
	}
}

void UIKFootBoneEffector::TickEnterReleaseIK(float DeltaTime)
{
	IKAlpha -= GetTickIKAlphaValue(DeltaTime, EnterIKAlphaSpeed);
	UMerinoLogStatics::LogFloat("Release IK Alpha: ", GetTickIKAlphaValue(DeltaTime, EnterIKAlphaSpeed));
	UMerinoLogStatics::LogFloat("Release IK Alpha: ", IKAlpha);
	if (IKAlpha <= 0.0f)
	{
		CurrentState = Inactive;
		IKAlpha = 0.0f;
	}
}