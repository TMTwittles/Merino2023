// Fill out your copyright notice in the Description page of Project Settings.
#include "..\..\..\Public\CharacterMovement\MovementStateData\JumpingMovementStateData.h"

float UJumpingMovementStateData::CalculateInitialVelocityZ() const
{
	return (2 * MaxJumpHeight) / TimeReachMaxJumpHeightSeconds;
}

float UJumpingMovementStateData::CalculateGravity() const
{
	return (-2.0f * MaxJumpHeight) / (TimeReachMaxJumpHeightSeconds * TimeReachMaxJumpHeightSeconds);
}
