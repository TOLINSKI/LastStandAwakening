// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	// ...
	StartLocation = GetOwner()->GetActorLocation();
	IsTriggered = false;
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if(IsTriggered)
	{
		GoToLocation = TargetLocation;
	}
	else
	{
		GoToLocation = StartLocation;
	}
	MoveToTarget();
}

void UMover::MoveToTarget()
{
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	if (FVector::Dist(GoToLocation, CurrentLocation) > 5)
	{
		FVector MoveDir = (GoToLocation - CurrentLocation).GetSafeNormal();
		Velocity = MoveDir * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
		GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + Velocity); 
	 	UKismetMathLibrary::VInterpTo(
	 		GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + Velocity, 
	 		UGameplayStatics::GetWorldDeltaSeconds(this), 0.5);
	}
	else
	{
		GetOwner()->SetActorLocation(GoToLocation);
	}
}

void UMover::Reset()
{
	GetOwner()->SetActorLocation(StartLocation);
	IsTriggered = false;
}