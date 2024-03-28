// Fill out your copyright notice in the Description page of Project Settings.
#include "HSFM/States/GroundedState.h"
#include "CharacterMovement/MerinoMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UGroundedState::PostInitialise(AActor* Owner)
{
	MovementComponent = Owner->GetComponentByClass<UMerinoMovementComponent>();
}

void UGroundedState::TickState(float DeltaTime)
{
	FVector InputVector = MovementComponent->ConsumeInputVector();
	if (InputVector != FVector::Zero())
	{
		FVector InputVectorNormalized = InputVector.GetSafeNormal();
		MovementComponent->TickAcceleration(DeltaTime, InputVectorNormalized);
		MovementComponent->TickRotateToVector(DeltaTime, InputVectorNormalized);
	}
	else
	{
		MovementComponent->TickDeceleration(DeltaTime);
	}
	MovementComponent->Update();
}
