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
	float GetTickIKAlphaValue(float DeltaTime, float Speed) const;
	void TickEnterActiveIK(float DeltaTime);
	void TickEnterReleaseIK(float DeltaTime);
private:
	UPROPERTY()
	TObjectPtr<UWorld> World;
	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
	UPROPERTY()
	FName BoneName;
	UPROPERTY()
	TEnumAsByte<EIKState> CurrentState;
	UPROPERTY()
	float IKAlpha;
	UPROPERTY()
	float IKCheckDistance;
	UPROPERTY()
	FVector EffectorLocation;
	UPROPERTY()
	float ElapsedIKAlpaTickTime;
	UPROPERTY()
	float EnterIKAlphaSpeed;
	UPROPERTY()
	float ReleaseIKAlphaSpeed;
	UPROPERTY()
	float FootPositionAdjustmentAmount;
};
