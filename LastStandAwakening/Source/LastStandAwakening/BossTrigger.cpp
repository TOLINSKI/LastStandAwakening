// Fill out your copyright notice in the Description page of Project Settings.


#include "BossTrigger.h"
#include "RolyPoly.h"


// Sets default values
UBossTrigger::UBossTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void UBossTrigger::BeginPlay()
{
	Super::BeginPlay();

    BossIsFree = false;
	
}


// Called every frame
void UBossTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!BossIsFree)
    {
        TArray<AActor*> Actors;
	    GetOverlappingActors(Actors);
        if (BlockLifted(Actors))
        {
            ARolyPoly* Boss = Cast<ARolyPoly>(GetOwner());
            Boss->SetShouldStandUp(true);
            Boss->PlayStandUpSound();
            BossIsFree = true;
        }
    }
    
}

bool UBossTrigger::BlockLifted(TArray<AActor*> Actors)
{
    for (AActor* Actor: Actors)
    {
        if (Actor->ActorHasTag(TEXT("BossBlock")))
        {
            return false;
        }
    }
    return true;
}

void UBossTrigger::Reset()
{
    BossIsFree = false;
}