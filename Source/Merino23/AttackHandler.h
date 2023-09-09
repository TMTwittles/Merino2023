// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"

struct FAttackCombo;

/**
 * 
 */
class MERINO23_API FAttackHandler
{
public:
	FAttackHandler(UAnimInstance* AnimInstance, FAttackCombo* _AttackCombo);
	~FAttackHandler();
	void PlayAttack() const;

private:
	FAttackCombo* AttackCombo;
	UAnimInstance* AnimInstance;
};
