// Fill out your copyright notice in the Description page of Project Settings.
#include "MerinoCharacter.h"
#include "MerinoMathStatics.h"
#include "DynamicMovingCamera.h"
#include "CharacterMovement/MerinoMovementComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AMerinoCharacter::AMerinoCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Movement = CreateDefaultSubobject<UMerinoMovementComponent>("MovementComponent");
	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>("CapsuleCollider");
	SetRootComponent(CapsuleCollider);
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("PawnMesh");
	Mesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AMerinoCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Spawn camera to follow loco pawn. 
	SpawnedCamera = Cast<ADynamicMovingCamera>(GetWorld()->SpawnActor(Camera));
	if (SpawnedCamera != nullptr)
	{
		SpawnedCamera->Configure(this);
	}
}

// Called every frame
void AMerinoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMerinoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void AMerinoCharacter::AddControllerMovementInput(float InputX, float InputY)
{
	FVector InputDirectionNoRotation = FVector(InputY, InputX, 0.0f);
	if (SpawnedCamera != nullptr)
	{
		FQuat CameraRotation = SpawnedCamera->GetActorTransform().GetRotation();
		FQuat CameraRotationYawOnly = UMerinoMathStatics::BuildQuatEuler(UMerinoMathStatics::GetYawFromQuat(CameraRotation), 0.0f, 0.0f);
		FVector InputDirectionRotated = CameraRotationYawOnly * InputDirectionNoRotation;
		AddMovementInput(InputDirectionRotated);
	}
	else
	{
		AddMovementInput(InputDirectionNoRotation);
	}
}

void AMerinoCharacter::AddControllerCameraPitchInput(float PitchInput)
{
	SpawnedCamera->AddPitch(PitchInput);
}

void AMerinoCharacter::AddControllerCameraYawInput(float YawInput)
{
	SpawnedCamera->AddYaw(YawInput);
}

