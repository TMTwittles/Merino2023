// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterMovement/MerinoMovementComponent.h"
#include "MerinoMathStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "MerinoDebugStatics.h"

void UMerinoMovementComponent::BeginPlay()
{
	SetUpdatedComponent(GetOwner()->GetRootComponent());
	Super::BeginPlay();
}

const bool UMerinoMovementComponent::CharacterGrounded()
{
	FHitResult HitResult;
	FVector LineTraceStart = GetOwner()->GetActorLocation();
	FVector LineTraceEnd = LineTraceStart - GetOwner()->GetActorUpVector() * CheckGroundLineTraceDistance;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, LineTraceStart, LineTraceEnd, ECC_WorldStatic);
	return bHit;
}

void UMerinoMovementComponent::StickToGround()
{
	FHitResult HitResult;
	FVector LineTraceStart = GetOwner()->GetActorLocation();
	FVector LineTraceEnd = LineTraceStart - GetOwner()->GetActorUpVector() * CheckGroundLineTraceDistance;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, LineTraceStart, LineTraceEnd, ECC_WorldStatic);
	if (bHit)
	{
		GetOwner()->SetActorLocation(HitResult.ImpactPoint + GetOwner()->GetActorUpVector() * 50.0f);
	}
}

void UMerinoMovementComponent::ApplyImpulseForce(const float ImpulseForce, const FVector Direction)
{
	Velocity += Direction * ImpulseForce;
}

void UMerinoMovementComponent::TickRotateToVector(const float DeltaTime, const FVector TargetVector)
{
	FVector ActorForwardVector = GetOwner()->GetActorForwardVector();
	float TargetRotationAmount = UMerinoMathStatics::GetSignedAngleBetweenTwoVectorsRelativeToAxis
	(
		ActorForwardVector,
		TargetVector,
		GetOwner()->GetActorUpVector());
	TargetRotationAmountDegrees = FMath::RadiansToDegrees(TargetRotationAmount);
	float TickRotationAmount = FMath::Lerp(0.0f, TargetRotationAmount, DeltaTime) * AngularAcceleration;
	FQuat CurrentActorRotation = GetOwner()->GetActorRotation().Quaternion();
	FQuat TickRotation = FQuat(GetOwner()->GetActorUpVector(), TickRotationAmount);
	UpdatedActorRotation = CurrentActorRotation * TickRotation;
}

// TODO: Add input amount to the calculations.
void UMerinoMovementComponent::TickAcceleration(const FVector Direction, const float InputAmountNormalized)
{
	FVector NewVelocity = Velocity + Direction * Acceleration;
	NewVelocity = NewVelocity.GetClampedToSize(0.0f, MaxSpeed);
	Velocity = NewVelocity;
}

void UMerinoMovementComponent::TickGravity()
{
	FVector DownwardsVelocity = -GetOwner()->GetActorUpVector() * Gravity;
	FVector NewVelocity = Velocity + DownwardsVelocity;
	NewVelocity = NewVelocity.GetClampedToSize(0.0f, MaxFallingSpeed);
	Velocity = NewVelocity;
}

void UMerinoMovementComponent::TickDeceleration(const float DeltaTime)
{
	// Already slowed down. No need.
	if (Velocity == FVector::Zero())
	{
		return;
	}

	// Set deceleration vector opposing the direction of our velocity scaled by deceleration amount.
	FVector DecelerationVector = -Velocity.GetSafeNormal() * Deceleration;
	
	if (DecelerationVector.Size() >= Velocity.Size())
	{
		DecelerationVector = -Velocity;
	}

	FVector DecelerationVelocity = Velocity + DecelerationVector;
	DecelerationVelocity = DecelerationVelocity.GetClampedToSize(0.0f, MaxSpeed);
	Velocity = DecelerationVelocity;
}

void UMerinoMovementComponent::Update()
{
	UpdateComponentVelocity();
	MoveUpdatedComponent(Velocity, UpdatedActorRotation, false);
}
