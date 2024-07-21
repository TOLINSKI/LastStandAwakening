// Fill out your copyright notice in the Description page of Project Settings.


#include "Scales.h"
#include "Components/BoxComponent.h"
#include "../Protagonist.h"
#include "Kismet/GameplayStatics.h"
#include "Trophy.h"
#include "Engine.h"

// Sets default values
AScales::AScales()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Mesh"));
	SetRootComponent(Mesh);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(FName("TriggerBox"));
	TriggerBox->SetupAttachment(Mesh);

	RightScaleCollisionBox = CreateDefaultSubobject<UBoxComponent>(FName("RightScaleCollision"));
	RightScaleCollisionBox->SetupAttachment(Mesh);

	LeftScaleCollisionBox = CreateDefaultSubobject<UBoxComponent>(FName("LeftScaleCollision"));
	LeftScaleCollisionBox->SetupAttachment(Mesh);

	/*
	TrophyChild = CreateDefaultSubobject<UChildActorComponent>(FName("Trophy"));
	TrophyChild->SetupAttachment(Mesh);
	TrophyChild->SetChildActorClass(TrophyClass);
	*/

	AngleOffset = 0.f;
	AccumulateAngle = 0.f;
}

// Called when the game starts or when spawned
void AScales::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform, FName("scale_l_trigger_socket"));

	RightScaleCollisionBox->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform, FName("scale_l_collision_socket"));

	LeftScaleCollisionBox->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform, FName("scale_r_collision_socket"));

	Player = Cast<AProtagonist>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	for (TObjectPtr<ATrophy> TrophyIterator : TActorRange<ATrophy>(GetWorld()))
	{
		Trophy = TrophyIterator;
	}
	if (Trophy)
	{
		Trophy->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("scale_r_object_socket"));
	}
}

// Called every frame
void AScales::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> OverlappingActors;
	TriggerBox->GetOverlappingActors(OverlappingActors);

	for (TObjectPtr<AActor> Actor : OverlappingActors)
	{
		// TODO: Logic 
		if (!Actor->ActorHasTag(TEXT("scales")) && !Actor->ActorHasTag(TEXT("Grabbed")))
		{
			UE_LOG(LogTemp, Display, TEXT("Scales Overlapping: %s"), *Actor->GetName());
			if (Actor->GetComponentByClass<UStaticMeshComponent>() && Actor != Player)
			{
				// Actor->GetComponentByClass<UStaticMeshComponent>()->SetSimulatePhysics(false);
				Actor->GetComponentByClass<UStaticMeshComponent>()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				// Actor->GetComponentByClass<UStaticMeshComponent>()->SetEnableGravity(false);
				// Actor->GetComponentByClass<UStaticMeshComponent>()->AttachToComponent(Mesh, FAttachmentTransformRules::KeepWorldTransform, FName("scale_l_trigger_socket"));
			}

			if (Actor->ActorHasTag("weight"))
			{
				AccumulateAngle += 15.f;
			}
			else if (Actor->ActorHasTag("secondObject"))
			{
				AccumulateAngle += 10.f;
			}
			else if (Actor == Player)
			{
				AccumulateAngle += 15.f;
			}

			AngleOffset = AccumulateAngle;
			AccumulateAngle = 0.f;
		}
	}
}

