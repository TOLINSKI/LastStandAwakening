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
	PrimaryComponentTick.bCanEverTick = false;

    GameWinCondition = FString("Sclaes are equalibrium");
}

// Called when the game starts or when spawned
void UTargetTrigger::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UTargetTrigger::OnTargetBeginOverlap);
}

void UTargetTrigger::OnTargetBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Ball_8") && GameWinConditionMet())
	{
		SetGameWon();
	}
}

bool UTargetTrigger::GameWinConditionMet()
{
	return Scales && Scales->GetAngleOffset() == Scales->WinWeight;
}

void UTargetTrigger::SetGameWon()
{
	TObjectPtr<ALastStandGameMode> GameMode = GetWorld()->GetAuthGameMode<ALastStandGameMode>();
	if (GameMode)
	{
		GameMode->GameWon();
	}
}
