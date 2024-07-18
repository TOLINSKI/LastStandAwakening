// Fill out your copyright notice in the Description page of Project Settings.


#include "RolyPoly.h"
#include "Kismet/GameplayStatics.h"
#include "LastStandGameMode.h"
#include "BossTrigger.h"
#include "Shaker.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ARolyPoly::ARolyPoly()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>((TEXT("RootComponent")));
	SetRootComponent(Capsule);

	Shaker = CreateDefaultSubobject<UShaker>((TEXT("Shaker")));
	Shaker->SetupAttachment(RootComponent);

	bStartShake = false;
}

// Called when the game starts or when spawned
void ARolyPoly::BeginPlay()
{
	Super::BeginPlay();

	// Setup Variables
	ShouldStandUp = false;
	Shaker->SetShakeParams(0.5f, 90.f); // Params: (Shake Frequency multiplier, Amplitude)

	// Setup Locaions & Rotations
	StartLocation = GetActorLocation();
	StartRotation = GetActorRotation();
	StandRotation.Yaw = 90.f;

	// Setup Meshes:
	TArray<TObjectPtr<UStaticMeshComponent>> Meshes;
	GetComponents<UStaticMeshComponent>(Meshes);
	if (Meshes[0])
	{
		BodyMesh = Meshes[0];
	}
	if (Meshes[1])
	{
		HeadMesh = Meshes[1];
	}
	BodyMeshStartLocation = BodyMesh->GetComponentLocation();
	BodyMeshStartRotation = BodyMesh->GetComponentRotation();
}

// Called every frame
void ARolyPoly::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ShouldStandUp)
	{
		StandUp();
	}
}

void ARolyPoly::StandUp()
{
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	FRotator ActorRotation = GetActorRotation();
	
	// Interp to vetical roation & Location -> Shake & Interp to vertical Location 
	if (!bStartShake && !BodyMesh->GetComponentRotation().Equals(StandRotation, 20))
	{
		BodyMesh->SetWorldRotation(FMath::RInterpTo(
			BodyMesh->GetComponentRotation(),
			StandRotation,
			DeltaTime,
			15.f));
	}
	else if (!bStartShake && StandUpSound)
	{
		bStartShake = true;
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			StandUpSound,
			BodyMesh->GetComponentLocation());
		bStartShake = true;
	}

	if (bStartShake)
	{
		Shaker->ShakeRoly(BodyMesh);
	}

	if (FVector::Dist(BodyMesh->GetComponentLocation(), StandLocation) > 1)
	{
		BodyMesh->SetWorldLocation(FMath::VInterpTo(
			BodyMesh->GetComponentLocation(),
			StandLocation,
			DeltaTime,
			20.f));
	}
}
 
// Initiated By BossTrigger.cpp
void ARolyPoly::SetShouldStandUp(bool value)
{
	ShouldStandUp = value;
}

void ARolyPoly::Reset()
{
	UE_LOG(LogTemp, Error, TEXT("Roly Reset"));

	UBossTrigger* Trigger = Cast<UBossTrigger>(GetComponentByClass(UBoxComponent::StaticClass()));
	Trigger->Reset();
	Shaker->Reset();
	ShouldStandUp = false;
	bStartShake = false;

	SetActorLocation(StartLocation, false, nullptr, ETeleportType::ResetPhysics);
	SetActorRotation(StartRotation,ETeleportType::ResetPhysics);
	BodyMesh->SetWorldLocation(BodyMeshStartLocation);
	BodyMesh->SetWorldRotation(BodyMeshStartRotation);

	Shaker->SetShakeParams(0.5f, 90.f);
}