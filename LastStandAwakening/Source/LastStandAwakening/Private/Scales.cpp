// Fill out your copyright notice in the Description page of Project Settings.


#include "Scales.h"
#include "Components/BoxComponent.h"
#include "../Protagonist.h"
#include "Kismet/GameplayStatics.h"
#include "Trophy.h"
#include "Engine.h"
#include "Engine/SpotLight.h"
#include "TimerManager.h"

#define SCALES_WIN_WEIGHT 18.f

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

	AngleOffset = 0.f;
	AccumulateAngle = 0.f;
	PrevAngleOffset = 0.f;
	bAngleChanged = false;
	bHasPlayedSequence = false;
	WinWeight = SCALES_WIN_WEIGHT;
}

// Called when the game starts or when spawned
void AScales::BeginPlay()
{
	Super::BeginPlay();

	bWaitingForCamera = false;

	TriggerBox->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform, FName("scale_l_trigger_socket"));

	RightScaleCollisionBox->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform, FName("scale_l_collision_socket"));

	LeftScaleCollisionBox->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform, FName("scale_r_collision_socket"));

	Player = Cast<AProtagonist>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	// UPROPERTY() Trophy is set in blueprint:
	if (Trophy)
	{
		Trophy->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("scale_r_object_socket"));
	}

	// UPROPERTY() TargetLight is set in blueprint:
	if (TargetLight)
	{
		TargetLight->SetEnabled(false);
	}
}

// Called every frame
void AScales::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateScalesAngle();

	if (AngleOffset == SCALES_WIN_WEIGHT)
	{
		if (TargetLight)
		TargetLight->SetEnabled(true);
		if (!bHasPlayedSequence)
		{
			PlaySequence();
			bHasPlayedSequence = true;
		}
	}
	else
	{
		if (TargetLight)
		TargetLight->SetEnabled(false);
	}
}

void AScales::UpdateScalesAngle()
{
	TArray<AActor*> OverlappingActors;
	TriggerBox->GetOverlappingActors(OverlappingActors);

	for (TObjectPtr<AActor> Actor : OverlappingActors)
	{
		if (Actor != this && !Actor->ActorHasTag(TEXT("Grabbed")))
		{
			UE_LOG(LogTemp, Display, TEXT("Scales Overlapping: %s"), *Actor->GetName());
			if (Actor == Player)
			{
				AccumulateAngle += 25.f;
				AccumulateAngle += GetWeight(Player->GetGrabbedActor());
			}
			else
			{
				AccumulateAngle += GetWeight(Actor);
			}
		}
	}
	AngleOffset = AccumulateAngle;
	AccumulateAngle = 0.f;
}

float AScales::GetWeight(TObjectPtr<AActor> Actor)
{
	if (!Actor)
	{
		return 0.f;
	}
	else if (Actor->ActorHasTag("weight"))
	{
		return 30.f;
	}
	else if (Actor->ActorHasTag("Ball_1"))
	{
		return 1.f;
	}
	else if (Actor->ActorHasTag("Ball_3"))
	{
		return 3.f;
	}
	else if (Actor->ActorHasTag("Ball_8"))
	{
		return 8.f;
	}
	else if (Actor->ActorHasTag("Ball_10"))
	{
		return 10.f;
	}
	else if (Actor->ActorHasTag("Ball_13"))
	{
		return 13.f;
	}
	else if (Actor->ActorHasTag("Ball_14"))
	{
		return 14.f;
	}
	else if (Actor->ActorHasTag("weight"))
	{
		return 25.f;
	}
	else
	{
		return 0.f;
	}
}
