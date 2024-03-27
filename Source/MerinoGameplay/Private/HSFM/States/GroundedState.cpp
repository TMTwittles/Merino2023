// Fill out your copyright notice in the Description page of Project Settings.
#include "HSFM/States/GroundedState.h"
#include "CharacterMovement/MerinoMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MerinoLogStatics.h"

UGroundedState::~UGroundedState()
{
	MovementComponent = nullptr;
}

void UGroundedState::PostInitialise(AActor* Owner)
{
	MovementComponent = Owner->GetComponentByClass<UMerinoMovementComponent>();
}

void UGroundedState::TickState(float DeltaTime)
{
	FVector InputVector = MovementComponent->ConsumeInputVector();
	if (InputVector != FVector::Zero())
	{
		float InputAmountNormalized = UKismetMathLibrary::NormalizeToRange(InputVector.Size(), 0.0f, 1.0f);
		FVector InputVectorNormalized = InputVector.GetSafeNormal();
		MovementComponent->TickAcceleration(DeltaTime, InputVectorNormalized, InputAmountNormalized);
		MovementComponent->TickRotateToVector(DeltaTime, InputVectorNormalized);
	}
	else
	{
		MovementComponent->TickDeceleration(DeltaTime);
	}
	MovementComponent->Update();
	UMerinoLogStatics::LogFloat("Movement amount: ", MovementComponent->Velocity.Size());
}
