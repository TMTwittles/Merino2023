// Fill out your copyright notice in the Description page of Project Settings.
#include "HSFM/States/JumpingState.h"
#include "HSFM/StateProperties/MerinoStateProperties.h"
#include "CharacterMovement/MerinoMovementComponent.h"
#include "MerinoLogStatics.h"
#include "MerinoMathStatics.h"
#include "MerinoDebugStatics.h"
#include "Kismet/KismetMathLibrary.h"

void UJumpingState::EnterState()
{
	//Super::EnterState();
	/*FVector JumpDirection = CalculateJumpDirection();
	InitialJumpAngle = UMerinoMathStatics::GetUnsignedAngleBetweenTwoVectors(MovementComponent->Velocity.GetSafeNormal(), JumpDirection);
	MovementComponent->ApplyImpulseForce(JumpForce, CalculateJumpDirection());
	MovementComponent->Update();
	CalculateJumpAttributes();*/
}

void UJumpingState::TickState(float DeltaTime)
{
	//FVector InputVector = MovementComponent->ConsumeInputVector();
	//TickNormalizedJumpProgress();
	//if (InputVector != FVector::Zero())
	//{
	//	//FVector InputVectorNormalized = InputVector.GetSafeNormal();
	//	//MovementComponent->TickAcceleration(InputVectorNormalized);
	//	//MovementComponent->TickRotateToVector(DeltaTime, InputVectorNormalized);
	//}
	//else
	//{
	//	//MovementComponent->TickDeceleration(DeltaTime);
	//}
	//MovementComponent->TickGravity();
	//MovementComponent->Update();
}

void UJumpingState::PostInitialise(AActor* InOwner, UMerinoStateProperties* InStateProperties)
{
	/*Super::PostInitialise(InOwner, InStateProperties);
	Owner = InOwner;
	JumpForce = InStateProperties->GetFloatProperty("Jump force");*/
}

void UJumpingState::CalculateJumpAttributes()
{
	/*StartJumpHeight = MovementComponent->GetActorLocation().Z;
	FVector InitialJumpVelocity = MovementComponent->Velocity * FMath::Sin(InitialJumpAngle);
	float YInitialJumpVelocity = InitialJumpVelocity.Z;
	MaxJumpHeight = (YInitialJumpVelocity * YInitialJumpVelocity) / (2 * (MovementComponent->Gravity));
	MaxJumpHeight += StartJumpHeight;*/
}

void UJumpingState::TickNormalizedJumpProgress()
{
	/*NormalizedJumpProgress = (MovementComponent->GetActorLocation().Z - StartJumpHeight) / (MaxJumpHeight - StartJumpHeight);
	NormalizedJumpProgress = FMath::Clamp(NormalizedJumpProgress, 0.0f, 1.0f);
	UMerinoLogStatics::LogFloat("Normalized jump progress = ", NormalizedJumpProgress);*/
}

FVector UJumpingState::CalculateJumpDirection()
{
	//float CurrentSpeed = MovementComponent->Velocity.Size();
	//float NormalizedSpeedAmount = UKismetMathLibrary::NormalizeToRange(CurrentSpeed, 0.0f, MaxSpeed);
	//FVector VelocityNormalized = MovementComponent->Velocity.GetSafeNormal();
	//float MaxRotationAmount = UMerinoMathStatics::GetUnsignedAngleBetweenTwoVectors(VelocityNormalized, Owner->GetActorUpVector());
	//float MinRotationAmount = MinimumJumpAnglePercentage * MaxRotationAmount;
	//float RotationAmount = MaxRotationAmount;
	//// TODO: Have speed amount affect rotation amount, instead of being so binary. 
	//if (NormalizedSpeedAmount > 0.0f)
	//{
	//	RotationAmount = MinRotationAmount;
	//	FVector Cross = FVector::CrossProduct(VelocityNormalized, Owner->GetActorUpVector());
	//	return FQuat(Cross, RotationAmount).RotateVector(VelocityNormalized);
	//}
	//else
	//{
	//	return Owner->GetActorUpVector();
	//}
	return FVector::Zero();
}
