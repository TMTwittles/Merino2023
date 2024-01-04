// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MerinoMovementComponent.generated.h"

enum EMerinoMovementStateKey : int;
class UMerinoMovementState;
class UGroundedMovementState;
class ADynamicMovingCamera;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMovementStateChanged);

UCLASS(ClassGroup=Movement, meta=(BlueprintSpawnableComponent))
class MERINOGAMEPLAY_API UMerinoMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction) override;
	const bool CharacterGrounded();
	void UpdateIKFootPositions();
	void UpdatePelvisRotation();
	void TickRotateToVector(float DeltaTime, FVector TargetVector);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MovementAttributes)
	float MovementAngleDegrees;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MovementAttributes)
	float Deceleration;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MovementAttributes)
	float Acceleration;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MovementAttributes)
	float MaxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MovementAttributes)
	float CheckGroundLineTraceDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MovementAttributes)
	float Gravity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MovementAttributes)
	float MaxFallingSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MovementAttributes)
	float AngularSpeed;

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
	
	UPROPERTY(BlueprintAssignable)
	FMovementStateChanged MovementStateChanged;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=FootIK)
	FVector RightFootPosition;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=FootIK)
	FVector LeftFootPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=FootIK)
	float IKLineTraceDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="True"), Category=FootIK)
	float FootIKDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=PelvisRotation)
	FQuat PelvisRotation;
	
	FQuat UpdatedActorRotation;
private:
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="True"))
	TEnumAsByte<EMerinoMovementStateKey> ActiveMovementStateKey;
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="True"))
	UMerinoMovementState* ActiveMovementState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="True"))
	TMap<TEnumAsByte<EMerinoMovementStateKey>, UMerinoMovementState*> MovementStateMap;
};
