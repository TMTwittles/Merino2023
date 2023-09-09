// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Pawn.h"
#include "SimpleLocoPawn.generated.h"

class USimpleLocoPawnMovementComponent;
class ASimpleLocoPawnCamera;
class UCameraMovementComponent;
class UCameraComponent;
class UCapsuleComponent;
class FAttackHandler;
class USkeletalMeshComponent;

UCLASS()
class MERINO23_API ASimpleLocoPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASimpleLocoPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void PlayAttack();
	void PlayAttack01();
	void CheckMovementInput();
	void DrawInputDebugHelpers() const;

	UPROPERTY(Category=Movement, EditAnywhere, BlueprintReadWrite)
	USimpleLocoPawnMovementComponent* Movement;
	

private:
	FAttackHandler* AttackHandler;
	ASimpleLocoPawnCamera* SpawnedCamera;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"));
	TSubclassOf<ASimpleLocoPawnCamera> Camera;  
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess="true"))
	UCapsuleComponent* CapsuleCollider;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess="true"))
	USkeletalMeshComponent* Mesh;
	
	//UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true,RowType="AttackCombo"))
	//FDataTableRowHandle* CharacterAttack;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess="true"))
	UAnimMontage* AttackAnim;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess="true"))
	UAnimMontage* AttackAnim01;
	
	FVector InputDirection;
};
