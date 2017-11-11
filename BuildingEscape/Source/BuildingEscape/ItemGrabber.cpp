// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemGrabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Public/DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"

//does nothing, just to annotate that some parameters are changed as output ("getted" in this way)
#define OUT		


// Sets default values for this component's properties
UItemGrabber::UItemGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UItemGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();
	SetupInputComponent();
}

// Called every frame
void UItemGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// if the physics handle is attached
	if (PhysicsHandle->GrabbedComponent) {
		/// move the object that we're holding
		CalculateLineTraceEnd();
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}


	

}

// Look for attached Physics Handle Component
void UItemGrabber::FindPhysicsHandleComponent() {
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("The object %s doesn't have a Physic Handle Component attached to it!"), *GetOwner()->GetName());
	}
}

// Setup (assumed) attached Input component
void UItemGrabber::SetupInputComponent() {
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("Input component found!"));
		/// Bind the grab action
		InputComponent->BindAction("Grab",					//ActionName
			IE_Pressed,				//KeyEvent
			this,					//Object that operates
			&UItemGrabber::Grab);	//Reference to the Method to be called
									/// Bind the release action
		InputComponent->BindAction("Grab", IE_Released, this, &UItemGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("The object %s doesn't have a Input Component attached to it!"), *GetOwner()->GetName());
	}
}

// For debugging
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

}

void UItemGrabber::LogViewPoint() {
	UE_LOG(LogTemp, Warning, TEXT("Location : %s, Rotation : %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString())
}

const FHitResult UItemGrabber::GetFirstPhysicsBodyInReach() {
	CalculateLineTraceEnd();
	/// Setup query parameters
	FCollisionObjectQueryParams ObjectQuery(ECollisionChannel::ECC_PhysicsBody);
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

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
	return Hit;
}

void UItemGrabber::CalculateLineTraceEnd() {
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector()*Reach);
}

void UItemGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab key pressed."))

	/// LINE-TRACE and see if we reach any actors with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	/// If we hit something then attach a physic handle
	if (ActorHit) {
		PhysicsHandle->GrabComponent(	ComponentToGrab,														//Primitive Component
										NAME_None,																//Bone Name
										ComponentToGrab->GetOwner()->GetActorLocation(),						//Grab Location
										true);																	//Allow Rotation?
	}
	
}

void UItemGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Item released."))
	PhysicsHandle->ReleaseComponent();
}
