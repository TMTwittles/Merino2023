// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicMovingCamera.generated.h"

class UCameraComponent;
class UCameraMovementComponent;

UCLASS()
class MERINO23_API ADynamicMovingCamera : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ADynamicMovingCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Configure(AActor* ActorToFollow);
	
	UFUNCTION(BlueprintCallable)
	void AddYaw(float YawInc);

	UFUNCTION(BlueprintCallable)
	void AddPitch(float PitchInc);
	float GetYaw();
	float GetPitch();

private:

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	UCameraMovementComponent* CameraMovementComponent;

};
