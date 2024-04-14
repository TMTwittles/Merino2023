// Fill out your copyright notice in the Description page of Project Settings.
#include "MerinoCharacter.h"
#include "MerinoMathStatics.h"
#include "DynamicMovingCamera.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterMovement/MerinoMovementComponent.h"
#include "CharacterMovement/MovementStateControllerComponent.h"
#include "CharacterMovement/MovementStates/MerinoMovementStateKey.h"
#include "CharacterMovement/MovementStates/MovementStateBehaviours/BehaviourController.h"
#include "CharacterMovement/MovementStates/MovementStateBehaviours/LockOnMovementStateBehaviour.h"
#include "CharacterMovement/MovementStates/MovementStateBehaviours/MovementStateBehaviourKey.h"
#include "Components/CapsuleComponent.h"
#include "IK/FootIKSolverComponent.h"
#include "HSFM/MerinoStateMachineComponent.h"
#include "RegisteredActionsComponent.h"
#include "RegisteredActionID.h"

// Sets default values
AMerinoCharacter::AMerinoCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Build actor components
	CharacterMovementComponent = CreateDefaultSubobject<UCharacterMovementComponent>("Character movement component");
	CharacterMovementComponent->SetComponentTickEnabled(true);
	CharacterMovementComponent->PrimaryComponentTick.bCanEverTick = true;
	Movement = CreateDefaultSubobject<UMerinoMovementComponent>("MovementComponent");
	FootIKSolver = CreateDefaultSubobject<UFootIKSolverComponent>("FootIKSolverComponent");
	RegisteredActionsComponent = CreateDefaultSubobject<URegisteredActionsComponent>("RegisteredActionComponent");
	RegisteredActionsComponent->SetComponentTickEnabled(true);
	RegisteredActionsComponent->PrimaryComponentTick.bCanEverTick = true;
	StateMachineComponent = CreateDefaultSubobject<UMerinoStateMachineComponent>("StateMachineComponent");
	StateMachineComponent->SetComponentTickEnabled(true);
	StateMachineComponent->PrimaryComponentTick.bCanEverTick = true;

	// Build scene components
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

void AMerinoCharacter::AddControllerJumpInput()
{
	RegisteredActionsComponent->RegisterAction(JumpAction);
}

