// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleLocoPawnCamera.h"
#include "CameraMovementComponent.h"
#include "Camera/CameraComponent.h"

static const FName NAME_CamX("CamX");
static const FName NAME_CamY("CamY");

// Sets default values
ASimpleLocoPawnCamera::ASimpleLocoPawnCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraMovementComponent = CreateDefaultSubobject<UCameraMovementComponent>("Movement");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
}

// Called when the game starts or when spawned
void ASimpleLocoPawnCamera::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASimpleLocoPawnCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASimpleLocoPawnCamera::ConfigureSimpleLocoPawnCamera(AActor* ActorToFollow)
{
	CameraMovementComponent->ConfigureCameraPositionRotation(ActorToFollow, Camera);
	GetWorld()->GetFirstPlayerController()->SetViewTarget(this);
}

void ASimpleLocoPawnCamera::AddYawPitch(float YawInc, float PitchInc)
{
	CameraMovementComponent->UpdateCameraYawPitch(YawInc, PitchInc);
}

float ASimpleLocoPawnCamera::GetYaw()
{
	return CameraMovementComponent->Yaw;
}

float ASimpleLocoPawnCamera::GetPitch()
{
	return CameraMovementComponent->Pitch;
}

