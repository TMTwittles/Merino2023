// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterMovement\MovementStates\GroundedMovementState.h"

#include "MerinoLogStatics.h"
#include "MerinoMathStatics.h"
#include "CharacterMovement/MerinoMovementComponent.h"

UGroundedMovementState::UGroundedMovementState()
{
}

void UGroundedMovementState::Tick(float DeltaTime)
{
	FVector CurrentInputVector = MovementComponent->ConsumeInputVector();
	UMerinoLogStatics::LogVector("Current input vector: ", CurrentInputVector);
	MovementComponent->Velocity = CurrentInputVector * MovementComponent->Speed;
	if (CurrentInputVector != FVector::Zero())
	{
		TickFaceVector(DeltaTime, CurrentInputVector);	
	}
	MovementComponent->UpdateComponentVelocity();
	MovementComponent->MoveUpdatedComponent(MovementComponent->Velocity, UpdatedActorRotation, false);
}

void UGroundedMovementState::TickFaceVector(float DeltaTime, FVector TargetVector)
{
	FVector InputDirection = TargetVector.GetSafeNormal();
	FVector ActorForwardVector = MovementComponent->GetOwner()->GetActorForwardVector();
	float TargetRotationAmount = UMerinoMathStatics::GetSignedAngleBetweenTwoVectorsRelativeToAxis
	(
		ActorForwardVector,
		InputDirection, MovementComponent->GetOwner()->GetActorUpVector());
	float TickRotationAmount = FMath::Lerp(0.0f, TargetRotationAmount, DeltaTime * MovementComponent->AngularSpeed);

	FQuat CurrentActorRotation = MovementComponent->GetOwner()->GetActorRotation().Quaternion();
	FQuat TickRotation = FQuat(MovementComponent->GetOwner()->GetActorUpVector(), TickRotationAmount);
	UpdatedActorRotation = CurrentActorRotation * TickRotation;
}
