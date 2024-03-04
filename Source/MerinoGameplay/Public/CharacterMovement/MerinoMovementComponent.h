// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MerinoMovementComponent.generated.h"

enum EStateID : int;
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
	UFUNCTION(BlueprintCallable, BlueprintPure)
	const bool CharacterGrounded();
	void TickRotateToVector(float DeltaTime, FVector TargetVector);
	void TickAcceleration(float DeltaTime, FVector Direction);
	void TickDeceleration(float DeltaTime);
	void Update();

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
	float AngularRotationSpeed;

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
	FQuat UpdatedActorRotation;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="True"))
	TEnumAsByte<EStateID> ActiveMovementStateKey;
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="True"))
	UMerinoMovementState* ActiveMovementState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="True"))
	TMap<TEnumAsByte<EStateID>, UMerinoMovementState*> MovementStateMap;
	UPROPERTY()
	FVector LastActiveVelocity;
};
