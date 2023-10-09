// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MerinoMovementComponent.generated.h"

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
	void SetCamera(ADynamicMovingCamera* _PawnCamera);


public:
	UPROPERTY(BlueprintReadWrite, Category=MovementInfo, meta=(AllowPrivateAccess="true"))
	float MovementAngleDegrees;
	
private:

	ADynamicMovingCamera* PawnCamera; 
	
	const float InputDiffDegreesRequiresRecalculationThreshold = 30.0f;
	const float MaxRotationAmount = 180.0f;

	const bool CharacterFalling();
	void TickRotateToCamera(float DeltaTime);
	void TickRotateToInput(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MovementAttributes, meta=(AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MovementAttributes, meta=(AllowPrivateAccess= "true"))
	float CheckGroundLineTraceDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MovementAttributes, meta=(AllowPrivateAccess= "true"))
	float Gravity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MovementAttributes, meta=(AllowPrivateAccess= "true"))
	float AngularSpeed;

	bool ForceRecalculateRotation;
	float TargetRotationAmount;
	float TargetTimeSecondsRotateToInput;
	float CurrentRotationAmount;
	float ElapsedRotationTime;
	float RotationDelta;
	FQuat UpdatedActorRotation;
	FVector CurrentInputVector;
	FVector PreviousInputVector;
};
