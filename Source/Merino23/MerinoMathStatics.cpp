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
	return FMath::Clamp(Dot, -1.0f, 1.0f) * UnsignedAngleBetweenTwoVectors;
}


