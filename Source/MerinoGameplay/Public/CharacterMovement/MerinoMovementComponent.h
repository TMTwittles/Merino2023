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
	const bool CharacterGrounded();
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
	float AngularSpeed;

	UFUNCTION(BlueprintCallable)
	void SetActiveMovementState(EMerinoMovementStates MovementStates);

	UFUNCTION(BlueprintCallable)
	void AddMovementState(EMerinoMovementStates MovementStates, UMerinoMovementState* _MovementState);
	
	FQuat UpdatedActorRotation;
private:
	UMerinoMovementState* ActiveMovementState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="True"))
	TMap<TEnumAsByte<EMerinoMovementStates>, UMerinoMovementState*> MovementStateMap;
};
