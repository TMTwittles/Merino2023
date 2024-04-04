// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MerinoMovementComponent.generated.h"

UCLASS(ClassGroup=Movement, meta=(BlueprintSpawnableComponent))
class MERINOGAMEPLAY_API UMerinoMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	const bool CharacterGrounded();
	void TickRotateToVector(const float DeltaTime, FVector TargetVector);
	void TickAcceleration(const FVector Direction, const float InputAmountNormalized = 1.0f);
	void TickDeceleration(const float DeltaTime);
	void Update();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MovementAttributes)
	float MovementAngleDegrees;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MovementAttributes)
	float TargetRotationAmountDegrees = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MovementAttributes)
	float MaxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MovementAttributes)
	float Acceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MovementAttributes)
	float Deceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MovementAttributes)
	float AngularAcceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MovementAttributes)
	float CheckGroundLineTraceDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MovementAttributes)
	float Gravity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MovementAttributes)
	float MaxFallingSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MovementAttributes)
	float MaxJumpHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MovementAttributes)
	float StartingJumpGravity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MovementAttributes)
	float MaxJumpGravity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MovementAttributes)
	float AirControl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MovementAttributes)
	float NormalizedJumpProgress;

private:
	UPROPERTY()
	FQuat UpdatedActorRotation;
};
