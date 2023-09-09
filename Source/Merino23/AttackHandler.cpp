// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackHandler.h"
#include "FAttackCombo.h"

FAttackHandler::FAttackHandler(UAnimInstance* _AnimInstance, FAttackCombo* _AttackCombo)
{
	AnimInstance = _AnimInstance;
	AttackCombo = _AttackCombo;
}

FAttackHandler::~FAttackHandler()
{
}

void FAttackHandler::PlayAttack() const
{
	AnimInstance->Montage_Play(AttackCombo->AttackAnimMontage);
}
