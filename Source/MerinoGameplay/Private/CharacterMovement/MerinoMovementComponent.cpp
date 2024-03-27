// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterMovement/MerinoMovementComponent.h"
#include "MerinoMathStatics.h"
#include "MerinoLogStatics.h"
#include "MerinoDebugStatics.h"
#include "Kismet/KismetMathLibrary.h"

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
	TargetRotationAmountDegrees = FMath::RadiansToDegrees(TargetRotationAmount);
	UMerinoLogStatics::LogFloat("Target rotation amount: ", TargetRotationAmountDegrees);
	float TickRotationAmount = FMath::Lerp(0.0f, TargetRotationAmount, DeltaTime) * AngularRotationSpeed;
	FQuat CurrentActorRotation = GetOwner()->GetActorRotation().Quaternion();
	FQuat TickRotation = FQuat(GetOwner()->GetActorUpVector(), TickRotationAmount);
	UpdatedActorRotation = CurrentActorRotation * TickRotation;
}

void UMerinoMovementComponent::TickAcceleration(float DeltaTime, FVector Direction, float InputAmountNormalized)
{
	// Set to velocity, used to calculate deceleration.
	LastActiveVelocity = Velocity;
	FVector NewVelocity = Velocity + Direction * Acceleration;
	NewVelocity *= InputAmountNormalized;
	NewVelocity = NewVelocity.GetClampedToSize(0.0f, MaxSpeed);
	UMerinoDebugStatics::DrawSingleFrameDebugSphere(GetWorld(), GetOwner()->GetActorLocation() + NewVelocity.Size() * NewVelocity.GetSafeNormal(), 10.0f, FColor::Red);
	UMerinoLogStatics::LogFloat("Velocity size: ", NewVelocity.Size());
	UMerinoLogStatics::LogVector("New velocity: ", NewVelocity);
	
	if (MovementAmountNormalized < 1.0f)
	{
		MovementAmountNormalized = UKismetMathLibrary::NormalizeToRange(NewVelocity.Size(), 0.0f, MaxSpeed);
	}
	UMerinoLogStatics::LogFloat("Movement amount normalized: ", MovementAmountNormalized);


	Velocity = NewVelocity;
}

void UMerinoMovementComponent::TickDeceleration(float DeltaTime)
{
	UMerinoLogStatics::LogFloat("Movement amount normalized: ", MovementAmountNormalized);

	// Already slowed down. No need.
	if (Velocity == FVector::Zero())
	{
		MovementAmountNormalized = 0.0f;
		return;
	}

	// Set deceleration vector opposing the direction of our velocity scaled by deceleration amount.
	FVector DecelerationVector = -Velocity.GetSafeNormal() * Deceleration;
	
	// If deceleration vector greater than velocity, thus instantly end velocity. 
	if (DecelerationVector.Size() >= Velocity.Size())
	{
		DecelerationVector = -Velocity;
	}

	FVector DecelerationVelocity = Velocity + DecelerationVector;
	DecelerationVelocity = DecelerationVelocity.GetClampedToSize(0.0f, MaxSpeed);
	MovementAmountNormalized = UKismetMathLibrary::NormalizeToRange(DecelerationVelocity.Size(), 0.0f, MaxSpeed);
	Velocity = DecelerationVelocity;
}

void UMerinoMovementComponent::Update()
{
	UpdateComponentVelocity();
	MoveUpdatedComponent(Velocity, UpdatedActorRotation, false);
}
