// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "ItemGrabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UItemGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UItemGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void VisualizePlayerView();

	void LogViewPoint();



protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	//how far ahead of the player can we reach in cm
	float Reach = 100.0f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	// Return hit for the first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();

	//Ray-cast and grab what's in reach
	void Grab();

	//Called when Grab is released
	void Release();

	// Look for attached Physics Handle Component
	void FindPhysicsHandleComponent();

	// Setup (assumed) attached Input component
	void SetupInputComponent();

};
