// Fill out your copyright notice in the Description page of Project Settings.
#include "CameraMovement/CameraMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UCameraMovementComponent::UCameraMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UCameraMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UCameraMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TickCameraPosition();
}

void UCameraMovementComponent::ConfigureCameraPositionRotation(AActor* TrackingActor, const UCameraComponent* Camera)
{
	if (TrackingActor == nullptr)
	{
		return;
	}
	
	TanFOVY = UKismetMathLibrary::Tan(FMath::DegreesToRadians(0.5f * Camera->FieldOfView));
	TanFOVX = TanFOVY * Camera->AspectRatio;
	LocalOffset = FVector(
		Distance,
		Distance * TanFOVX * Framing.X,
		Distance * TanFOVY * Framing.Y);
	
	ActorToTrack = TrackingActor;

	FQuat FinalRotation = CalculateFinalRotation();
	FVector FinalPosition = ActorToTrack->GetTransform().GetLocation() - CalculateFinalRotation() * LocalOffset;
	GetOwner()->SetActorLocationAndRotation(FinalPosition, FinalRotation);
	ConfiguredCamera = true;
}

void UCameraMovementComponent::UpdateCameraYawPitch(float YawInc, float PitchInc)
{
	Yaw += YawInc;
	Pitch += PitchInc;
}

FQuat UCameraMovementComponent::CalculateFinalRotation()
{
	FQuat RotationYaw = FQuat(ActorToTrack->GetTransform().GetLocation().UpVector, FMath::DegreesToRadians(Yaw));
	FQuat RotationPitch = FQuat(ActorToTrack->GetTransform().GetLocation().RightVector, FMath::DegreesToRadians(Pitch));
	return RotationYaw * RotationPitch;
}

void UCameraMovementComponent::TickCameraPosition()
{
	if (ConfiguredCamera == false)
	{
		return;
	}
	
	FQuat FinalRotation = CalculateFinalRotation();
	FVector FinalPosition = ActorToTrack->GetTransform().GetLocation() - CalculateFinalRotation() * LocalOffset;
	GetOwner()->SetActorLocationAndRotation(FinalPosition, FinalRotation);
}


