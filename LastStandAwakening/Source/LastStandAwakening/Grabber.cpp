// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle && PhysicsHandle -> GetGrabbedComponent())
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle -> SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}	

	
	/*

	Getting the camera rotation and World time:
	===========================================

	FRotator CameraRotation = GetComponentRotation();
	FString CameraRotationCoordinates = CameraRotation.ToCompactString();

	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetName());
	UE_LOG(LogTemp, Display, TEXT("Rotation: %s"), *CameraRotationCoordinates);

	UWorld *World = GetWorld();

	float TimeSeconds = World->GetTimeSeconds();

	UE_LOG(LogTemp, Display, TEXT("Time Seconds: %f"), TimeSeconds);

	*/

	// FVector Start = GetComponentLocation();
	// FVector End = Start + GetForwardVector() * MaxGrabDistance;

	/*
	Debugging a Red line from direction of camera:
	===============================================
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	float& DamageRef = Damage;
	DamageRef = 5;

	UE_LOG(LogTemp, Display, TEXT("Original damage is: %f || DamageRef is: %f"), Damage, DamageRef);
	*/
}

void UGrabber::Grab()
{
	if (Grabbing)
	{
		Release();
		Grabbing = false;
		return;
	}
	Grabbing = true;
	// Use Grab only if the Owner has PhysicsHandleComponent:
	// ======================================================
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if(!PhysicsHandle)
	{
		return;
	}

	FHitResult HitResult;
	bool IsHit = GetGrabbableInReach(HitResult);
	if (IsHit)
	{
		// Grabbing using PhysicsHandle when ChannelSweep makess a hit:
		// ============================================================
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent -> WakeAllRigidBodies(); // The physics engine needs wake up when interacted with
		HitComponent -> SetSimulatePhysics(true);
		AActor * HitActor = HitResult.GetActor();
		HitActor -> Tags.Add("Grabbed");
		// HitActor -> DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		PhysicsHandle -> GrabComponentAtLocationWithRotation(
			HitResult.GetComponent(),
			NAME_None, // For static mesh, when skeleton mesh do something else
			HitResult.ImpactPoint,
			GetComponentRotation()// This is the rotation of the grabbed object
		);

		// -------------------------------------------------------------------------------------
		// Displaying the Actor who was hit by the ChannelSweep:
		// =====================================================
		// AActor* ActorHit = HitResult.GetActor();
		// UE_LOG(LogTemp, Display, TEXT("Hitting: %s"), *(ActorHit->GetName()));
		// -------------------------------------------------------------------------------------
		// Drawing Debug Sphere:
		// =====================
		// DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Green, false, 5);
		// DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Blue, false, 5);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Not Hitting Anything with Grabber component"));
		// DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Red, false, 5);
	}
}

void UGrabber::Release()
{
	UPhysicsHandleComponent * PhysicsHandle  = GetPhysicsHandle();
	if (PhysicsHandle && PhysicsHandle -> GetGrabbedComponent())
	{
		AActor* GrabbedActor = PhysicsHandle -> GetGrabbedComponent() -> GetOwner();
		GrabbedActor -> Tags.Remove("Grabbed");
		PhysicsHandle -> GetGrabbedComponent() -> WakeAllRigidBodies();
		PhysicsHandle -> ReleaseComponent();
	}
	
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	
	// Creating a Spherical Sweep -> TraceChannel is in 'DefaultEngine.ini', Search for 'Grabber'
	// ==========================================================================================
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	return GetWorld() -> SweepSingleByChannel(
				OutHitResult,
				Start,
				End,
				FQuat::Identity,
				ECC_GameTraceChannel2,
				Sphere
				);
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	// Use Grab only if the Owner has PhysicsHandleComponent:
	// ======================================================
	UPhysicsHandleComponent * PhysicsHandle =
	GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(!PhysicsHandle)
	{
		UE_LOG(LogTemp, Display, TEXT("The Grabbing component has no PhysicsHandleComponent!"));
	}

	return PhysicsHandle;
}