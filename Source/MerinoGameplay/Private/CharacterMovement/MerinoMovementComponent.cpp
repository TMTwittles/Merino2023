// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterMovement/MerinoMovementComponent.h"

#include "MerinoDebugStatics.h"
#include "MerinoMathStatics.h"

void UMerinoMovementComponent::BeginPlay()
{
	SetUpdatedComponent(GetOwner()->GetRootComponent());
	Super::BeginPlay();
}

void UMerinoMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateIKFootPositions();
	UpdatePelvisRotation();
}

const bool UMerinoMovementComponent::CharacterGrounded()
{
	FHitResult HitResult;
	FVector LineTraceStart = GetOwner()->GetActorLocation();
	FVector LineTraceEnd = LineTraceStart - GetOwner()->GetActorUpVector() * CheckGroundLineTraceDistance;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, LineTraceStart, LineTraceEnd, ECC_WorldStatic);
	return bHit;
}

void UMerinoMovementComponent::UpdateIKFootPositions()
{
	FVector ActorLocation = GetOwner()->GetActorLocation();
	FVector ActorRightVector = GetOwner()->GetActorRightVector();
	FVector LineTraceCheckVector = -GetOwner()->GetActorUpVector() * IKLineTraceDistance;
	FVector RightLineTraceStart = ActorLocation + (ActorRightVector * FootIKDistance);
	FVector LeftLineTraceStart = ActorLocation + (ActorRightVector * -FootIKDistance);
	FHitResult RightHitResult;
	FHitResult LeftHitResult;
	bool RightHit = GetWorld()->LineTraceSingleByChannel(RightHitResult, RightLineTraceStart, RightLineTraceStart + LineTraceCheckVector, ECC_WorldStatic);
	bool LeftHit = GetWorld()->LineTraceSingleByChannel(LeftHitResult, LeftLineTraceStart, LeftLineTraceStart + LineTraceCheckVector, ECC_WorldStatic);
	if (RightHit)
	{
		RightFootPosition = RightHitResult.ImpactPoint;
	}
	if (LeftHit)
	{
		LeftFootPosition = LeftHitResult.ImpactPoint;
	}
}

void UMerinoMovementComponent::UpdatePelvisRotation()
{
	
}

void UMerinoMovementComponent::TickRotateToVector(float DeltaTime, FVector TargetVector)
{
	FVector InputDirection = TargetVector.GetSafeNormal();
	FVector ActorForwardVector = GetOwner()->GetActorForwardVector();
	float TargetRotationAmount = UMerinoMathStatics::GetSignedAngleBetweenTwoVectorsRelativeToAxis
	(
		ActorForwardVector,
		InputDirection,
		GetOwner()->GetActorUpVector());
	float TickRotationAmount = FMath::Lerp(0.0f, TargetRotationAmount, DeltaTime * AngularSpeed);
	FQuat CurrentActorRotation = GetOwner()->GetActorRotation().Quaternion();
	FQuat TickRotation = FQuat(GetOwner()->GetActorUpVector(), TickRotationAmount);
	UpdatedActorRotation = CurrentActorRotation * TickRotation;
}
