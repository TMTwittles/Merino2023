// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterMovement/MerinoMovementComponent.h"
#include "MerinoMathStatics.h"

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

void UMerinoMovementComponent::TickRotateToVector(float DeltaTime, FVector TargetVector)
{
	FVector ActorForwardVector = GetOwner()->GetActorForwardVector();
	float TargetRotationAmount = UMerinoMathStatics::GetSignedAngleBetweenTwoVectorsRelativeToAxis
	(
		ActorForwardVector,
		TargetVector,
		GetOwner()->GetActorUpVector());
	float TickRotationAmount = FMath::Lerp(0.0f, TargetRotationAmount, DeltaTime) * AngularRotationSpeed;
	FQuat CurrentActorRotation = GetOwner()->GetActorRotation().Quaternion();
	FQuat TickRotation = FQuat(GetOwner()->GetActorUpVector(), TickRotationAmount);
	UpdatedActorRotation = CurrentActorRotation * TickRotation;
}

void UMerinoMovementComponent::TickAcceleration(float DeltaTime, FVector Direction)
{
	// Set to velocity, used to calculate deceleration.
	LastActiveVelocity = Velocity;
	FVector NewVelocity = Velocity + Direction * Acceleration * DeltaTime;
	NewVelocity = NewVelocity.GetClampedToSize(0.0f, MaxSpeed);
	Velocity = NewVelocity;
}

void UMerinoMovementComponent::TickDeceleration(float DeltaTime)
{
	// Already slowed down. No need.
	if (Velocity == FVector::Zero())
	{
		return;
	}

	// Set deceleration vector opposing the direction of our velocity scaled by deceleration amount.
	FVector DecelerationVector = -Velocity.GetSafeNormal() * Deceleration;
	FVector DecelerationVelocity = Velocity + DecelerationVector * DeltaTime;
	DecelerationVelocity = DecelerationVelocity.GetClampedToSize(0.0f, DecelerationVelocity.Size());
	Velocity = DecelerationVelocity;
}

void UMerinoMovementComponent::Update()
{
	UpdateComponentVelocity();
	MoveUpdatedComponent(Velocity, UpdatedActorRotation, false);
}
