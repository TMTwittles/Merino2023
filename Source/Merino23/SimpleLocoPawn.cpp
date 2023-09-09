// Fill out your copyright notice in the Description page of Project Settings.
#include "SimpleLocoPawn.h"

#include "GameFramework/PawnMovementComponent.h"
#include "AttackHandler.h"
#include "FAttackCombo.h"
#include "MerinoMathStatics.h"
#include "SimpleLocoCharacter.h"
#include "SimpleLocoPawnCamera.h"
#include "SimpleLocoPawnMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"

static const FName NAME_MoveX("MoveX");
static const FName NAME_MoveY("MoveY");
static const FName NAME_CamX("CamX");
static const FName NAME_CamY("CamY");
static const FName NAME_Attack("Attack");
static const FName NAME_Attack01("Attack01");

// Sets default values
ASimpleLocoPawn::ASimpleLocoPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Movement = CreateDefaultSubobject<USimpleLocoPawnMovementComponent>("Movement");
	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>("CapsuleCollider");
	SetRootComponent(CapsuleCollider);
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("PawnMesh");
	Mesh->SetupAttachment(GetRootComponent());
	//Mesh->SetupAttachment(GetRootComponent());
	
}

// Called when the game starts or when spawned
void ASimpleLocoPawn::BeginPlay()
{
	Super::BeginPlay();

	// Spawn camera to follow loco pawn. 
	SpawnedCamera = Cast<ASimpleLocoPawnCamera>(GetWorld()->SpawnActor(Camera));
	if (SpawnedCamera != nullptr)
	{
		SpawnedCamera->ConfigureSimpleLocoPawnCamera(this);
		Movement->SetCamera(SpawnedCamera);
	}
}

// Called every frame
void ASimpleLocoPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckMovementInput();

	if (SpawnedCamera != nullptr)
	{
		SpawnedCamera->AddYawPitch(GetInputAxisValue(NAME_CamX), GetInputAxisValue(NAME_CamY));
	}
	//DrawInputDebugHelpers();
	AddMovementInput(InputDirection);
}

// Called to bind functionality to input
void ASimpleLocoPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(NAME_MoveX);
	PlayerInputComponent->BindAxis(NAME_MoveY);
	PlayerInputComponent->BindAxis(NAME_CamX);
	PlayerInputComponent->BindAxis(NAME_CamY);
	PlayerInputComponent->BindAction(NAME_Attack, IE_Pressed, this, &ASimpleLocoPawn::PlayAttack);
	PlayerInputComponent->BindAction(NAME_Attack01, IE_Pressed, this, &ASimpleLocoPawn::PlayAttack01);
}

void ASimpleLocoPawn::PlayAttack()
{
	float played = Mesh->GetAnimInstance()->Montage_Play(AttackAnim);
}

void ASimpleLocoPawn::PlayAttack01()
{
	float played = Mesh->GetAnimInstance()->Montage_Play(AttackAnim01);
}

void ASimpleLocoPawn::CheckMovementInput()
{
	/*UE_LOG(LogTemp, Log, TEXT("Move x input: %f"), GetInputAxisValue(NAME_MoveX));
	UE_LOG(LogTemp, Log, TEXT("Move y input: %f"), GetInputAxisValue(NAME_MoveY));
	UE_LOG(LogTemp, Log, TEXT("Cam z input: %f"), GetInputAxisValue(NAME_CamX));*/

	float InputY = GetInputAxisValue(NAME_MoveY);
	float InputX = GetInputAxisValue(NAME_MoveX);
	FVector InputDirectionRaw = FVector(InputY, InputX, 0.0f);
	if (SpawnedCamera != nullptr)
	{
		FQuat CameraRotation = SpawnedCamera->GetActorTransform().GetRotation();
		FQuat CameraRotationYawOnly = UMerinoMathStatics::BuildQuatEuler(UMerinoMathStatics::GetYawFromQuat(CameraRotation), 0.0f, 0.0f);
		FVector InputDirectionRotated = CameraRotationYawOnly * InputDirectionRaw;
		InputDirection = InputDirectionRotated;
	}
	else
	{
		InputDirection = InputDirectionRaw;
	}
	//UE_LOG(LogTemp, Log, TEXT("Input direction x: %f y: %f z: %f"), InputDirection.X, InputDirection.Y, InputDirection.Z);
}


void ASimpleLocoPawn::DrawInputDebugHelpers() const
{
	const float LineSize = 100.0f;
	const float CircleRadius = 20.0f;
	FVector actorLocation = GetActorLocation();
	FVector InputDirectionNormalized = InputDirection;
	//InputDirectionNormalized.Normalize();
	DrawDebugLine(GetWorld(),
	              actorLocation,
	              actorLocation + InputDirectionNormalized * LineSize,
	              FColor(0, 255, 0),
	              false);

	DrawDebugSphere(GetWorld(),
	                actorLocation + InputDirectionNormalized * LineSize,
	                CircleRadius,
	                10,
	                FColor(0, 255, 0));
}
