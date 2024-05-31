// Fill out your copyright notice in the Description page of Project Settings.


#include "RolyPoly.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARolyPoly::ARolyPoly()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARolyPoly::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARolyPoly::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!FinishStandUp && ShouldStandUp)
	{
		StandUp();
	}

}

void ARolyPoly::StandUp()
{
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	FRotator ActorRotation = GetActorRotation();

	if (!ActorRotation.Equals(StandRotation, 1))
	// {
	// 	SetActorRotation(StandRotation);
	// }
	{
		SetActorRotation(FMath::RInterpTo(
			ActorRotation, 
			StandRotation,
			DeltaTime,
			RInterpSpeed));
	}
	// else if (!ActorRotation.Equals(FRotator(0, 0, 180), 1))
	// {
	// 	SetActorRotation(FMath::RInterpTo(
	// 		ActorRotation, 
	// 		FRotator(0, 0, 90),
	// 		DeltaTime,
	// 		RInterpSpeed));
	// }

	if (FVector::Dist(GetActorLocation(), StandLocation) > 1)
	{
		SetActorLocation(FMath::VInterpTo(
			GetActorLocation(), 
			StandLocation,
			DeltaTime,
			VInterpSpeed));
	}
}

void ARolyPoly::SetShouldStandUp(bool value)
{
	ShouldStandUp = value;
}

