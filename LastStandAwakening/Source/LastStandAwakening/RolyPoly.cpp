// Fill out your copyright notice in the Description page of Project Settings.


#include "RolyPoly.h"
#include "Kismet/GameplayStatics.h"
#include "LastStandGameMode.h"
#include "BossTrigger.h"
#include "Shaker.h"

// Sets default values
ARolyPoly::ARolyPoly()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Shaker = CreateDefaultSubobject<UShaker>((TEXT("Shaker")));
	Shaker->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ARolyPoly::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	StartRotation = GetActorRotation();
	ShouldStandUp = false;

	Shaker->SetShakeParams(0.5f, 2.f);
}

// Called every frame
void ARolyPoly::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Shaker->ShakeHead(DeltaTime);

	// AddActorWorldRotation(FRotator(0.f, 0.f, Val));

	// AddActorWorldRotation(FRotator(0.f, 0.f, 5.f));


	/*
	if (ShouldStandUp)
	{
		StandUp();
	}
	*/
}

void ARolyPoly::StandUp()
{
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	FRotator ActorRotation = GetActorRotation();

	if (!ActorRotation.Equals(StandRotation, 1))
	{
		SetActorRotation(FMath::RInterpTo(
			ActorRotation, 
			StandRotation,
			DeltaTime,
			RInterpSpeed));
	}
	else
	{
		ShouldStandUp = false;	
		// ALastStandGameMode* GameMode = GetWorld()->GetAuthGameMode<ALastStandGameMode>();
		// if (GameMode)
		// {
		// 	GameMode->GameWon();
		// }
		ShowGameWonWidget();
	}

	if (FVector::Dist(GetActorLocation(), StandLocation) > 1)
	{
		SetActorLocation(FMath::VInterpTo(
			GetActorLocation(), 
			StandLocation,
			DeltaTime,
			VInterpSpeed));
	}
}

// Initiated By BossTrigger.cpp
void ARolyPoly::SetShouldStandUp(bool value)
{
	ShouldStandUp = value;
}

void ARolyPoly::Reset()
{
	ShouldStandUp = false;
	SetActorLocation(StartLocation, false, nullptr, ETeleportType::TeleportPhysics);
	SetActorRotation(StartRotation,ETeleportType::TeleportPhysics);
	UBossTrigger* Trigger = Cast<UBossTrigger>(GetComponentByClass(UBoxComponent::StaticClass()));
	Trigger->Reset();
}
