// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MerinoMovementComponent.generated.h"

enum EMerinoMovementStates : int;
class UMerinoMovementState;
class UGroundedMovementState;
class ADynamicMovingCamera;
/**
 * 
 */
UCLASS(ClassGroup=Movement, meta=(BlueprintSpawnableComponent))
class MERINOGAMEPLAY_API UMerinoMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void AddInputVector(FVector WorldVector, bool bForce) override;
	virtual FVector ConsumeInputVector() override;

public:
	UPROPERTY(BlueprintReadWrite, Category=MovementInfo, meta=(AllowPrivateAccess="true"))
	float MovementAngleDegrees;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MovementAttributes, meta=(AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MovementAttributes, meta=(AllowPrivateAccess= "true"))
	float CheckGroundLineTraceDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MovementAttributes, meta=(AllowPrivateAccess= "true"))
	float Gravity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MovementAttributes, meta=(AllowPrivateAccess= "true"))
	float AngularSpeed;

	UFUNCTION(BlueprintCallable)
	void SetActiveMovementState(EMerinoMovementStates MovementStates);
private:
	const float InputDiffDegreesRequiresRecalculationThreshold = 30.0f;
	const float MaxRotationAmount = 180.0f;
	const bool CharacterFalling();
	bool ForceRecalculateRotation;
	float TargetRotationAmount;
	float TargetTimeSecondsRotateToInput;
	float CurrentRotationAmount;
	float ElapsedRotationTime;
	float RotationDelta;
	FQuat UpdatedActorRotation;
	FVector CurrentInputVector;
	FVector PreviousInputVector;
	UMerinoMovementState* ActiveMovementState;
	TMap<TEnumAsByte<EMerinoMovementStates>, UMerinoMovementState*> MovementStateMap;
};
