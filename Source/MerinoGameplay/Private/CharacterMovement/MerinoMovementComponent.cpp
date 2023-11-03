// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterMovement/MerinoMovementComponent.h"
#include "MerinoMathStatics.h"
#include "CharacterMovement/MovementStates/FallingMovementState.h"
#include "CharacterMovement/MovementStates/GroundedMovementState.h"
#include "CharacterMovement/MovementStates/JumpingMovementState.h"
#include "CharacterMovement/MovementStates/MerinoMovementState.h"
#include "CharacterMovement/MovementStates/MerinoMovementStates.h"

void UMerinoMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	SetUpdatedComponent(GetOwner()->GetRootComponent());
	AddMovementState(Grounded, NewObject<UGroundedMovementState>());
	AddMovementState(Falling, NewObject<UFallingMovementState>());
	AddMovementState(Jumping, NewObject<UJumpingMovementState>());
	SetActiveMovementState(Grounded);
}

void UMerinoMovementComponent::Jump()
{
	SetActiveMovementState(EMerinoMovementStates::Jumping);
}


void UMerinoMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ActiveMovementState != nullptr)
	{
		ActiveMovementState->Tick(DeltaTime);	
	}
}

void UMerinoMovementComponent::AddInputVector(FVector WorldVector, bool bForce)
{
	Super::AddInputVector(WorldVector, bForce);
}

FVector UMerinoMovementComponent::ConsumeInputVector()
{
	return Super::ConsumeInputVector();
}

void UMerinoMovementComponent::SetActiveMovementState(EMerinoMovementStates MovementStates)
{
	TEnumAsByte<EMerinoMovementStates> Key = TEnumAsByte(MovementStates);
	if (MovementStateMap.Contains(Key))
	{
		ActiveMovementState = MovementStateMap[Key];
		ActiveMovementState->EnterMovementState();
	}
}

void UMerinoMovementComponent::AddMovementState(EMerinoMovementStates MovementStates, UMerinoMovementState* _MovementState)
{
	TEnumAsByte<EMerinoMovementStates> Key = TEnumAsByte(MovementStates);
	if (MovementStateMap.Contains(Key) == false)
	{
		MovementStateMap.Add(Key, _MovementState);
		MovementStateMap[Key]->ConfigureMovementState(this);
	}
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
	FVector InputDirection = TargetVector.GetSafeNormal();
	FVector ActorForwardVector = GetOwner()->GetActorForwardVector();
	float TargetRotationAmount = UMerinoMathStatics::GetSignedAngleBetweenTwoVectorsRelativeToAxis
	(
		ActorForwardVector,
		InputDirection, GetOwner()->GetActorUpVector());
	float TickRotationAmount = FMath::Lerp(0.0f, TargetRotationAmount, DeltaTime * AngularSpeed);

	FQuat CurrentActorRotation = GetOwner()->GetActorRotation().Quaternion();
	FQuat TickRotation = FQuat(GetOwner()->GetActorUpVector(), TickRotationAmount);
	UpdatedActorRotation = CurrentActorRotation * TickRotation;
}
