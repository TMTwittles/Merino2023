// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TransitionRule.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class MERINOGAMEPLAY_API UTransitionRule : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	bool ShouldTransition();
	UFUNCTION(BlueprintCallable)
	void SetShouldTransition(bool bInShouldTransition);
	UFUNCTION(BlueprintNativeEvent)
	void TickTransitionRule(float DeltaTime);
	UFUNCTION(BlueprintNativeEvent)
	void ConfigureTransitionRule(AActor* InOwner);
protected:
	bool bShouldTransition = false;
};
