// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RegisteredActionsComponent.generated.h"


enum ERegisteredActionID : int;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MERINO23_API URegisteredActionsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URegisteredActionsComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void RegisterAction(ERegisteredActionID ActionID);
	UFUNCTION(BlueprintCallable)
	bool ActionRegistered(ERegisteredActionID ActionID);

protected:
	void ClearRegisteredActions();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Actions to register", meta=(AllowPrivateAccess="True"))
	TArray<TEnumAsByte<ERegisteredActionID>> ActionsToRegister;
	UPROPERTY()
	TMap<TEnumAsByte<ERegisteredActionID>, int> RegisteredActionsMap;
};
