// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemGrabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Public/DrawDebugHelpers.h"

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

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	//TEST
	//LogViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	VisualizePlayerView();
}

void UItemGrabber::VisualizePlayerView() {

	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector()*Reach);
	/// Draw a red trace in the world to visualise
	DrawDebugLine(	GetWorld(),						//the world
					PlayerViewPointLocation,		//starting point	
					LineTraceEnd,					//line end
					FColor(255, 0, 0),				//colour
					false,							//is persistent?
					0.0f,							//life time 
					0.0f,							//depth priority		
					10.0f);							//thickness	

	/// Setup query parameters
	FCollisionObjectQueryParams ObjectQuery(ECollisionChannel::ECC_PhysicsBody);
	FCollisionQueryParams TraceParameters(FName(TEXT("")), true, GetOwner());

	/// Line-trace (AKA ray-cast) out to reach the distance
	FHitResult Hit;
	bool HasHit = false;
	HasHit = GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,									//Out-hit
		PlayerViewPointLocation,					//Start
		LineTraceEnd,								//End
		ObjectQuery,								//Object Query Params
		TraceParameters								//Collision Query Params
	);

	/// Log Hit
	if (HasHit) {
		UE_LOG(LogTemp, Warning, TEXT("Raycasted %s"), *(Hit.Actor->GetName()));
	}
}

void UItemGrabber::LogViewPoint() {
	UE_LOG(LogTemp, Warning, TEXT("Location : %s, Rotation : %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString())
}

