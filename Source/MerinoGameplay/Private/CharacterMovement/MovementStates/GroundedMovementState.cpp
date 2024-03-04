// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterMovement\MovementStates\GroundedMovementState.h"
#include "CharacterMovement\MerinoMovementComponent.h"
#include "..\..\..\Public\CharacterMovement\MovementStates\MerinoMovementStateKey.h"
#include "CharacterMovement/MovementStateControllerComponent.h"
#include "CharacterMovement/MovementStates/MovementStateBehaviours/BehaviourController.h"
#include "CharacterMovement/MovementStates/MovementStateBehaviours/MovementStateBehaviourKey.h"
#include "CharacterMovement/MovementStates/MovementStateBehaviours/LockOnMovementStateBehaviour.h"

void UGroundedMovementState::PostConfigure(UMovementStateData* Data)
{
	Super::PostConfigure(Data);
	LockOnBehaviour = BehaviourController->GetBehaviour<ULockOnMovementStateBehaviour>(LockOn);
}

UGroundedMovementState::UGroundedMovementState()
{
}

void UGroundedMovementState::OnEnter()
{
	StickToGround();
	LastActiveVelocity = FVector::Zero();
	MovementComponent->Velocity = FVector::Zero();
}

float UGroundedMovementState::CalculateNormalizedElapsedDecelerationTime()
{
	float TotalDecelerationTime = (float)LastActiveVelocity.Size() / MovementComponent->Deceleration;
	float ElapsedDecelerationTime = (MovementComponent->Velocity.Size() - MovementComponent->Deceleration) / MovementComponent->Deceleration;
	ElapsedDecelerationTime = TotalDecelerationTime - ElapsedDecelerationTime;
	return ElapsedDecelerationTime / TotalDecelerationTime;
}

void UGroundedMovementState::StickToGround()
{
	FHitResult HitResult;
	FVector LineTraceStart = MovementComponent->GetOwner()->GetActorLocation();
	FVector LineTraceEnd = LineTraceStart - MovementComponent->GetOwner()->GetActorUpVector() * MovementComponent->CheckGroundLineTraceDistance;
	bool bHit = World->LineTraceSingleByChannel(HitResult, LineTraceStart, LineTraceEnd, ECC_WorldStatic);

	if (bHit)
	{
		FVector EndLocation = HitResult.Location + HitResult.ImpactNormal * 42.0f;
		MovementComponent->GetOwner()->SetActorLocation(EndLocation);
	}
}

void UGroundedMovementState::Tick(float DeltaTime)
{
	// Set movement state to grounded if 
	if (MovementComponent->CharacterGrounded() == false)
	{
		Controller->SetActiveMovementState(Falling);
		return;
	}

	FVector CurrentInputVector = MovementComponent->ConsumeInputVector();
	FVector ClampedVelocity = FVector::Zero();
	if (CurrentInputVector != FVector::Zero())
	{
//		MovementComponent->TickVelocity(DeltaTime, CurrentInputVector);
		MovementComponent->TickRotateToVector(DeltaTime, ClampedVelocity);
	}
	else
	{
		if (MovementComponent->Velocity == FVector::Zero())
		{
			return;
		}
		
		if (LastActiveVelocity == FVector::Zero())
		{
			LastActiveVelocity = MovementComponent->Velocity;
		}
		float Alpha = CalculateNormalizedElapsedDecelerationTime();
		ClampedVelocity = FMath::Lerp(MovementComponent->Velocity, FVector::Zero(), Alpha);
	}
	ClampedVelocity = ClampedVelocity.GetClampedToSize(0.0f, MovementComponent->MaxSpeed);
	MovementComponent->Velocity = ClampedVelocity;
	MovementComponent->UpdateComponentVelocity();
//	MovementComponent->MoveUpdatedComponent(MovementComponent->Velocity, MovementComponent->UpdatedActorRotation, false);
}
