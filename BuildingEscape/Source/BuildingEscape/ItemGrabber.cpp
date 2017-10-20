// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemGrabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

//does nothing, just to annotate that some parameters are changed as output ("getted" in this way)
#define OUT		


// Sets default values for this component's properties
UItemGrabber::UItemGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UItemGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UItemGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	LogViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
}

void UItemGrabber::LogViewPoint(FVector PlayerViewPointLocation, FRotator PlayerViewPointRotation) {
	UE_LOG(LogTemp, Warning, TEXT("Location : %s, Rotation : %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString())
}

