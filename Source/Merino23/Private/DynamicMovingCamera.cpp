// Fill out your copyright notice in the Description page of Project Settings.
#include "DynamicMovingCamera.h"
#include "CameraMovement/CameraMovementComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ADynamicMovingCamera::ADynamicMovingCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraMovementComponent = CreateDefaultSubobject<UCameraMovementComponent>("Movement");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
}

// Called when the game starts or when spawned
void ADynamicMovingCamera::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADynamicMovingCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADynamicMovingCamera::Configure(AActor* ActorToFollow)
{
	CameraMovementComponent->ConfigureCameraPositionRotation(ActorToFollow, Camera);
	GetWorld()->GetFirstPlayerController()->SetViewTarget(this);
}

void ADynamicMovingCamera::AddYaw(float YawInc)
{
	CameraMovementComponent->UpdateCameraYaw(YawInc);
}

void ADynamicMovingCamera::AddPitch(float PitchInc)
{
	CameraMovementComponent->UpdateCameraPitch(PitchInc);
}

float ADynamicMovingCamera::GetYaw()
{
	return CameraMovementComponent->Yaw;
}

float ADynamicMovingCamera::GetPitch()
{
	return CameraMovementComponent->Pitch;
}

