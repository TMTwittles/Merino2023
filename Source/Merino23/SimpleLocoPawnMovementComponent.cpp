// Fill out your copyright notice in the Description page of Project Settings.
#include "SimpleLocoPawnMovementComponent.h"

#include "MerinoLogStatics.h"
#include "MerinoMathStatics.h"
#include "SAdvancedTransformInputBox.h"

void USimpleLocoPawnMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	SetUpdatedComponent(GetOwner()->GetRootComponent());
	ForceRecalculateRotation = true;
	TargetTimeSecondsRotateToInput = 0.0f;
	CurrentRotationAmount = 0.0f;
}

void USimpleLocoPawnMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CurrentInputVector = GetPendingInputVector();
	Velocity = CurrentInputVector * Speed;

	if (CharacterFalling())
	{
		Velocity.Z -= Gravity;
	}

	TickRotateToInput(DeltaTime);
	UpdateComponentVelocity();
	MoveUpdatedComponent(Velocity, UpdatedActorRotation, false);

	if (CurrentInputVector != FVector::Zero())
	{
		PreviousInputVector = CurrentInputVector;
	}

	ConsumeInputVector();
}

void USimpleLocoPawnMovementComponent::AddInputVector(FVector WorldVector, bool bForce)
{
	Super::AddInputVector(WorldVector, bForce);
}

FVector USimpleLocoPawnMovementComponent::ConsumeInputVector()
{
	return Super::ConsumeInputVector();
}

const bool USimpleLocoPawnMovementComponent::CharacterFalling()
{
	FHitResult HitResult;
	FVector LineTraceStart = GetOwner()->GetActorLocation();
	FVector LineTraceEnd = LineTraceStart - GetOwner()->GetActorUpVector() * CheckGroundLineTraceDistance;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, LineTraceStart, LineTraceEnd, ECollisionChannel::ECC_WorldStatic);
	return bHit == false;
}

void USimpleLocoPawnMovementComponent::TickRotateToInput(float DeltaTime)
{
	if (CurrentInputVector != FVector::Zero())
	{
		FVector InputDirection = CurrentInputVector.GetSafeNormal();
		FVector ActorForwardVector = GetOwner()->GetActorForwardVector();
		UMerinoLogStatics::LogVector("InputDirection", InputDirection);
		UMerinoLogStatics::LogVector("ActorForwardVector", ActorForwardVector);
		TargetRotationAmount = UMerinoMathStatics::GetSignedAngleBetweenTwoVectorsRelativeToAxis(ActorForwardVector, InputDirection, GetOwner()->GetActorUpVector());
		UMerinoLogStatics::LogFloat("Target rotation amount: ", FMath::RadiansToDegrees(TargetRotationAmount));
		UMerinoLogStatics::LogFloat("Current rotation amount: ", FMath::RadiansToDegrees(UpdatedActorRotation.GetAngle()));
		float Delta = FMath::Abs(TargetRotationAmount) / FMath::DegreesToRadians(180.0f);
		UMerinoLogStatics::LogFloat("Delta: ", Delta);
		CurrentRotationAmount = FMath::Lerp(0.0f, TargetRotationAmount, DeltaTime * AngularSpeed);
		UpdatedActorRotation = GetOwner()->GetActorRotation().Quaternion() * FQuat(GetOwner()->GetActorUpVector(), CurrentRotationAmount);
		UMerinoLogStatics::LogFloat("Update Actor rotation amount", FMath::RadiansToDegrees(UpdatedActorRotation.GetAngle()));
	}
}
