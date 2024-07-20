// Fill out your copyright notice in the Description page of Project Settings.


#include "Scales.h"
#include "Components/BoxComponent.h"
#include "../Protagonist.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AScales::AScales()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Mesh"));
	SetRootComponent(Mesh);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(FName("TriggerBox"));
	TriggerBox->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AScales::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform, FName("judgement_socket"));

	Player = Cast<AProtagonist>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

// Called every frame
void AScales::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TriggerBox->SetWorldLocation(Mesh->GetSocketLocation("judgement_socket"));

	TArray<FString> ActorNames;
	TArray<AActor*> OverlappingActors;
	TriggerBox->GetOverlappingActors(OverlappingActors);

	for (TObjectPtr<AActor> Actor : OverlappingActors)
	{
		// TODO: Logic 
		if (!Actor->ActorHasTag(TEXT("scales")))
		{
			UE_LOG(LogTemp, Display, TEXT("Scales Overlapping: %s"), *Actor->GetName());
			ActorNames.Add(Actor->GetName());
		}
	}

	if (ActorNames.Num() == 2 && ActorNames.Contains("GoodObject1") && ActorNames.Contains("GoodObect2"))
	{
		// Do Good logic
	}
	else
	{

	}
}

