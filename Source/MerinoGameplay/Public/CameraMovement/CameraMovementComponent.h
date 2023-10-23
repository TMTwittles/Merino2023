// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CameraMovementComponent.generated.h"


class UCameraComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MERINOGAMEPLAY_API UCameraMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCameraMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, Category="Camera Movement Settings")
	float Pitch; // vertical camera tilt.
	UPROPERTY(EditAnywhere, Category="Camera Movement Settings")
	float Yaw; // horizontal camera tilt.
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ConfigureCameraPositionRotation(AActor* TrackingActor, const UCameraComponent* Camera);
	void UpdateCameraYawPitch(float YawInc, float PitchInc);
	void UpdateCameraYaw(float YawInc);
	void UpdateCameraPitch(float PitchInc);
private:
	FQuat CalculateFinalRotation();
	void TickCameraPosition();

	float TanFOVY = 0.0f;
	float TanFOVX = 0.0f;
	FVector LocalOffset;
	AActor* ActorToTrack;

	UPROPERTY(EditAnywhere, Category="Camera Movement Settings", meta=(AllowPrivateAccess = "true"))
	FVector2D Framing; // 2D screen position to frame object.

	UPROPERTY(EditAnywhere, Category="Camera Movement Settings", meta=(AllowPrivateAccess = "true"))
	float Distance; // offset between camera and player.

	bool ConfiguredCamera = false;
};
