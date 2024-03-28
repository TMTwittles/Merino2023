// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "CharacterMovement/MovementStateData/MovementStateData.h"
#include "Engine/DataTable.h"
#include "GameFramework/Pawn.h"
#include "MerinoCharacter.generated.h"

class UMerinoStateMachineComponent;
class UFootIKSolverComponent;
enum EStateID : int;
class UMerinoMovementState;
class UGroundedMovementState;
class UMerinoMovementComponent;
class ADynamicMovingCamera;
class UCameraMovementComponent;
class UCameraComponent;
class UCapsuleComponent;
class USkeletalMeshComponent;

UCLASS()
class MERINO23_API AMerinoCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMerinoCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable)
	void AddControllerMovementInput(float InputX, float InputY);

	UFUNCTION(BlueprintCallable)
	void AddControllerCameraPitchInput(float PitchInput);

	UFUNCTION(BlueprintCallable)
	void AddControllerCameraYawInput(float YawInput);

	UFUNCTION(BlueprintCallable)
	void AddControllerJumpInput();

	UFUNCTION(BlueprintCallable)
	void EnterLockOn();

	UFUNCTION(BlueprintCallable)
	void ReleaseLockOn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(Category=Movement, EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMerinoMovementComponent> Movement;

	UPROPERTY(Category=StateMachine, EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMerinoStateMachineComponent> StateMachineComponent;
	
	UPROPERTY(Category=IK, EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UFootIKSolverComponent> FootIKSolver;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	TObjectPtr<ADynamicMovingCamera> SpawnedCamera;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"));
	TSubclassOf<ADynamicMovingCamera> Camera;  
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UCapsuleComponent> CapsuleCollider;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USkeletalMeshComponent> Mesh;
};
