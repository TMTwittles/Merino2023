// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterMovement/MovementStates/MovementStateBehaviours/LockOnMovementStateBehaviour.h"

#include "CharacterMovement/MerinoMovementComponent.h"
#include "CharacterMovement/MovementStates/MerinoMovementState.h"

void ULockOnMovementStateBehaviour::TickBehaviour(float DeltaTime)
{
	
}

FVector ULockOnMovementStateBehaviour::GetLockOnDirection()
{
	return LockOnDirection;
}

FVector ULockOnMovementStateBehaviour::CalculateDirectionRelativeToLockOn(FVector InputDirection)
{
	return FVector::Zero();
}

void ULockOnMovementStateBehaviour::OnActive()
{
	LockOnDirection = MovementState->MovementComponent->GetOwner()->GetActorForwardVector();
}

void ULockOnMovementStateBehaviour::OnInActive()
{
	
}
