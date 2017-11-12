// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenDoor();
	void CloseDoor();

private:
	UPROPERTY(EditAnywhere)
	float OpenAngle = -90.0f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay;

	float LastDoorOpenTime;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	AActor* Owner;

	UPROPERTY(EditAnywhere)
	float TriggerMass = 30.f;

	float GetTotalMassOfActorsOnPlate();
	
};
