// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetTrigger.h"
#include "LastStandGameMode.h"

// Sets default values
UTargetTrigger::UTargetTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void UTargetTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UTargetTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

        TArray<AActor*> Actors;
	    GetOverlappingActors(Actors);

        if (BulletInTarget(Actors))
        {
            ALastStandGameMode* GameMode = GetWorld()->GetAuthGameMode<ALastStandGameMode>();
		    if (GameMode)
		    {
		    GameMode->GameWon();
		    }
        }
}

bool UTargetTrigger::BulletInTarget(TArray<AActor*> Actors)
{
    for (AActor* Actor: Actors)
    {
        if(Actor) 
        {
            UE_LOG(LogTemp, Display, TEXT("OverLapping: "));
        }
        if (Actor->ActorHasTag(TEXT("Bullet")))
        {
            return true;
        }
    }
    return false;
}