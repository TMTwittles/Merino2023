// Fill out your copyright notice in the Description page of Project Settings.
#include "SimpleLocoCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

static const FName NAME_MoveX("MoveX");
static const FName NAME_MoveY("MoveY");
static const FName NAME_CamX("CamX");

// Sets default values
ASimpleLocoCharacter::ASimpleLocoCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ASimpleLocoCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASimpleLocoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckMovementInput();
	DrawInputDebugHelpers();
}

// Called to bind functionality to input
void ASimpleLocoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(NAME_MoveX);
	PlayerInputComponent->BindAxis(NAME_MoveY);
	PlayerInputComponent->BindAxis(NAME_CamX);
}

void ASimpleLocoCharacter::CheckMovementInput()
{
	UE_LOG(LogTemp, Log, TEXT("Move x input: %f"), GetInputAxisValue(NAME_MoveX));
	UE_LOG(LogTemp, Log, TEXT("Move y input: %f"), GetInputAxisValue(NAME_MoveY));
	UE_LOG(LogTemp, Log, TEXT("Cam z input: %f"), GetInputAxisValue(NAME_CamX));

	float InputY = GetInputAxisValue(NAME_MoveY);
	float InputX = GetInputAxisValue(NAME_MoveX);
	InputDirection = FVector(InputY, InputX, 0.0f);
	
	UE_LOG(LogTemp, Log, TEXT("Input direction x: %f y: %f z: %f"), InputDirection.X, InputDirection.Y, InputDirection.Z);
}

void ASimpleLocoCharacter::DrawInputDebugHelpers() const
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

