// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "IKFootBoneEffector.generated.h"

enum EIKState : int;

/**
 * 
 */
UCLASS(Blueprintable)
class MERINOGAMEPLAY_API UIKFootBoneEffector : public UObject
{
	GENERATED_BODY()

public:
	UIKFootBoneEffector();
	void Initialize(UWorld* InWorld, USkeletalMeshComponent* InSkeletalMeshComponent, FName InBoneName, float InEnterIKAlphaSpeed, float InReleaseIKAlphaSpeed, float InIKCheckDistance, float InFootPositionAdjustmentAmount);
	void Ground();
	void Release();
	void Tick(float DeltaTime);
	UFUNCTION(BlueprintCallable)
	FVector GetEffectorLocation();
	UFUNCTION(BlueprintCallable)
	float GetIKAlpha();

private:
	FVector CalculateEffectorLocation();
	void TickUpdateIK(float DeltaTime, float StartAlpha, float EndAlpha, float UpdateAlphaSpeed, EIKState TargetState);
	
private:
	UPROPERTY()
	UWorld* World;
	UPROPERTY()
	USkeletalMeshComponent* SkeletalMeshComponent;
	FName BoneName;
	EIKState CurrentState;
	float IKAlpha;
	float IKCheckDistance;
	FVector EffectorLocation;
	float ElapsedIKAlpaTickTime;
	float EnterIKAlphaSpeed;
	float ReleaseIKAlphaSpeed;
	float FootPositionAdjustmentAmount;
};
