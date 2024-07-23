// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetTrigger.h"
#include "LastStandGameMode.h"
#include "Protagonist.h"
#include "Kismet/GameplayStatics.h"
#include "Scales.h"

// Sets default values
UTargetTrigger::UTargetTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;

    GameWinCondition = FString("Sclaes are equalibrium");
}

// Called when the game starts or when spawned
void UTargetTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	Player = Cast<AProtagonist>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	UE_LOG(LogTemp, Display, TEXT("Setting up TRIGGERRRRRRRR"));
}


// Called every frame
void UTargetTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GameWinConditionMet() && BallInTarget())
	{
		SetGameWon();
	}
}

bool UTargetTrigger::BallInTarget()
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (TObjectPtr<AActor> Actor : Actors)
	{
		if (Actor->ActorHasTag("Ball_8"))
		{
			UE_LOG(LogTemp, Warning, TEXT("Ball in target"));
			return true;
		}
	}
    return false;
}

bool UTargetTrigger::GameWinConditionMet()
{

	if (Scales && Scales->GetAngleOffset() == Scales->WinWeight)
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Win Confidition met"));
		return true;
	}
	return false;
}

bool UTargetTrigger::PlayerIsOverlapping()
{
	if (Player)
	{
		TArray<AActor*> Actors;
		GetOverlappingActors(Actors);

		for (AActor* Actor : Actors)
		{
			if (Actor == Player)
			{
				return true;
			}
		}
	}
	return false;
}

void UTargetTrigger::SetGameWon()
{
	TObjectPtr<ALastStandGameMode> GameMode = GetWorld()->GetAuthGameMode<ALastStandGameMode>();
	if (GameMode)
	{
		GameMode->GameWon();
	}
}
