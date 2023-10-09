// Fill out your copyright notice in the Description page of Project Settings.
#include "MerinoMathStatics.h"

float UMerinoMathStatics::GetUnsignedAngleBetweenTwoVectors(FVector From, FVector To)
{
	return acos(FVector::DotProduct(From, To));
}

float UMerinoMathStatics::GetSignedAngleBetweenTwoVectorsRelativeToAxis(FVector From, FVector To, FVector Axis)
{
	float UnsignedAngleBetweenTwoVectors = GetUnsignedAngleBetweenTwoVectors(From, To);
	FVector CrossProduct = FVector::CrossProduct(From, To);
	float Dot = FVector::DotProduct(CrossProduct, Axis);
	// Set dot multiplier to either 1.0 or -1.0 based dot product of cross product.
	float DotMultiplier = Dot > 0.0f ? 1.0f : -1.0f;
	return FMath::Clamp(DotMultiplier * UnsignedAngleBetweenTwoVectors, -180.0f, 180.0f);
}

float UMerinoMathStatics::GetYawFromQuat(FQuat Quat)
{
	return FMath::Atan2(2.0f*(Quat.Z*Quat.W+Quat.X*Quat.Y), -1.0f + 2.0f * (Quat.W*Quat.W - Quat.X*Quat.X));
}

float UMerinoMathStatics::GetPitchFromQuat(FQuat Quat)
{
	return FMath::Asin(-2.0f*(Quat.X*Quat.Z - Quat.W*Quat.Y));
}

FQuat UMerinoMathStatics::BuildQuatEuler(float Yaw, float Pitch, float Roll)
{
	FQuat YawQuat = FQuat(FVector::UpVector, Yaw);
	FQuat PitchQuat = FQuat(FVector::RightVector, Pitch);
	FQuat RollQuat = FQuat(FVector::ForwardVector, Roll);
	return YawQuat * PitchQuat * RollQuat;
}

FVector UMerinoMathStatics::CalculateCentroid(FVector P1, FVector P2, FVector P3)
{
	return (P1 + P2 + P3) / 3;
}
