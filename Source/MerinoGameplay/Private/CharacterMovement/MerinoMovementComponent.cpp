// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterMovement/MerinoMovementComponent.h"
#include "DynamicMovingCamera.h"
#include "CharacterMovement/MovementStates/GroundedMovementState.h"
#include "CharacterMovement/MovementStates/MerinoMovementState.h"
#include "CharacterMovement/MovementStates/MerinoMovementStates.h"

void UMerinoMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	SetUpdatedComponent(GetOwner()->GetRootComponent());
	ForceRecalculateRotation = true;
	TargetTimeSecondsRotateToInput = 0.0f;
	CurrentRotationAmount = 0.0f;
	MovementStateMap.Add(Grounded, NewObject<UGroundedMovementState>());
	MovementStateMap[Grounded]->ConfigureMovementState(this);
	SetActiveMovementState(Grounded);
}

void UMerinoMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (CharacterFalling())
	{
		Velocity.Z -= Gravity;
	}

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
	}
}

const bool UMerinoMovementComponent::CharacterFalling()
{
	FHitResult HitResult;
	FVector LineTraceStart = GetOwner()->GetActorLocation();
	FVector LineTraceEnd = LineTraceStart - GetOwner()->GetActorUpVector() * CheckGroundLineTraceDistance;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, LineTraceStart, LineTraceEnd, ECC_WorldStatic);
	return bHit == false;
}
