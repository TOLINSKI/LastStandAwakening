// Fill out your copyright notice in the Description page of Project Settings.


#include "RolyPoly.h"
#include "Kismet/GameplayStatics.h"
#include "LastStandGameMode.h"
#include "BossTrigger.h"
#include "Shaker.h"
#include "Components/CapsuleComponent.h"
#include "Public/RolyPolyAnimInstance.h"

// Sets default values
ARolyPoly::ARolyPoly()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>((TEXT("RootComponent")));
	SetRootComponent(Capsule);

	Shaker = CreateDefaultSubobject<UShaker>((TEXT("Shaker")));
	Shaker->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARolyPoly::BeginPlay()
{
	Super::BeginPlay();

	// Setup Variables
	Shaker->SetShakeParams(0.5f, 90.f); // Params: (Shake Frequency multiplier, Amplitude)

	// Setup Locaions & Rotations
	StartLocation = GetActorLocation();
	StartRotation = GetActorRotation();
	StandRotation.Yaw = 90.f;

	// Setup Meshes:
	BodyMesh = GetComponentByClass<USkeletalMeshComponent>();
	BodyMeshStartLocation = BodyMesh->GetComponentLocation();
	BodyMeshStartRotation = BodyMesh->GetComponentRotation();

	HeadMesh = GetComponentByClass<UStaticMeshComponent>();
	HeadMesh->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform, FName("head_socket"));
}

// Called every frame
void ARolyPoly::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldAnimate) // bShouldAnimate needs to be set manually in RolyPoly.h
	{
		if (ShouldStandUp)
		{
			StandUp();
		}

		if (bDoneShaking && PlayerInRange())
		{
			bShouldLook = true;
		}
		else
		{
			bShouldLook = false;
		}
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
		BodyMesh->SetWorldRotation(StandRotation);
		bStartShake = true;
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			StandUpSound,
			BodyMesh->GetComponentLocation());
		bStartShake = true;
		PlaySequence();
	}

	if (bStartShake)
	{
		Shaker->ShakeRoly(BodyMesh, bDoneShaking);
		if (bDoneShaking)
		{
			if (DartStepsHead)
			{
				DartStepsHead->SetActorTickEnabled(true);
			}
			ShouldStandUp = false;
		}
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
void ARolyPoly::SetShouldStandUp(bool Value)
{
	ShouldStandUp = Value;
}

void ARolyPoly::Reset()
{
	UBossTrigger* Trigger = Cast<UBossTrigger>(GetComponentByClass(UBoxComponent::StaticClass()));
	Trigger->Reset();
	Shaker->Reset();
	InitVariables();

	SetActorLocation(StartLocation, false, nullptr, ETeleportType::ResetPhysics);
	SetActorRotation(StartRotation,ETeleportType::ResetPhysics);
	BodyMesh->SetWorldLocation(BodyMeshStartLocation);
	BodyMesh->SetWorldRotation(BodyMeshStartRotation);

	Shaker->SetShakeParams(0.5f, 90.f);
}

bool ARolyPoly::PlayerInRange()
{
	if (TObjectPtr<APawn> Player = UGameplayStatics::GetPlayerPawn(this, 0))
	{
		return FVector::Dist(Player->GetActorLocation(), BodyMesh->GetComponentLocation()) < 1200.f;
	}
	return false;
}

void ARolyPoly::InitVariables()
{
	bStartShake = false;
	bDoneShaking = false;
	bShouldLook = false;
	ShouldStandUp = false;
	FinishStandUp = false;
}
