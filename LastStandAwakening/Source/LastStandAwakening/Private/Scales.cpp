// Fill out your copyright notice in the Description page of Project Settings.


#include "Scales.h"
#include "Components/BoxComponent.h"
#include "../Protagonist.h"
#include "Kismet/GameplayStatics.h"
#include "Trophy.h"
#include "Engine.h"
#include "Engine/SpotLight.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
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
	bShouldPlaySequence = false;
	bFirstScaleChange = true;
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

	Camera = Player->GetCamera();

	// SpringArm = Cast<USpringArmComponent>(Camera->GetAttachParent());

	// Setup Trophy:
	// ========================================================================
	for (TObjectPtr<ATrophy> TrophyIterator : TActorRange<ATrophy>(GetWorld()))
	{
		Trophy = TrophyIterator;
	}
	if (Trophy)
	{
		Trophy->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("scale_r_object_socket"));
	}
	// TODO: 
	// Adding Actor reference using the Actor reference tool 
	// 
	// UPROPERTY(BlueprintReadWrite, EditAnywhere, InstanceEditable) AActor* ScaleReference;

	// Setup TargetLight:
	// ========================================================================
	for (TObjectPtr<ASpotLight> SpotLightIterator : TActorRange<ASpotLight>(GetWorld()))
	{
		if (SpotLightIterator->ActorHasTag("target_light"))
		{
			TargetLight = SpotLightIterator;
			break;
		}
	}
	if (TargetLight)
	{
		TargetLight->SetEnabled(false);
	}

	// Setup CameraAngle:
	// ========================================================================
	for (TObjectPtr<AActor> CameraIterator : TActorRange<AActor>(GetWorld()))
	{
		if (CameraIterator->ActorHasTag("camera_angle_scales"))
		{
			CameraAngle = CameraIterator;
			break;
		}
	}
}

// Called every frame
void AScales::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateScalesAngle();

	if (AngleOffset == SCALES_WIN_WEIGHT)
	{
		TargetLight->SetEnabled(true);
	}
	else
	{
		TargetLight->SetEnabled(false);
	}
}

void AScales::UpdateScalesAngle()
{
	TArray<AActor*> OverlappingActors;
	TriggerBox->GetOverlappingActors(OverlappingActors);

	for (TObjectPtr<AActor> Actor : OverlappingActors)
	{
		// UE_LOG(LogTemp, Display, TEXT(" Has Actors"));
		// TODO: Logic 
		if (Actor.GetName() != GetName() && !Actor->ActorHasTag(TEXT("Grabbed")))
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
				AccumulateAngle += 30.f;
			}
			else if (Actor->ActorHasTag("Ball_1"))
			{
				AccumulateAngle += 1.f;
			}
			else if (Actor->ActorHasTag("Ball_3"))
			{
				AccumulateAngle += 3.f;
			}
			else if (Actor->ActorHasTag("Ball_8"))
			{
				AccumulateAngle += 8.f;
			}
			else if (Actor->ActorHasTag("Ball_10"))
			{
				AccumulateAngle += 10.f;
			}
			else if (Actor->ActorHasTag("Ball_13"))
			{
				AccumulateAngle += 13.f;
			}
			else if (Actor->ActorHasTag("Ball_14"))
			{
				AccumulateAngle += 14.f;
			}
			else if (Actor->ActorHasTag("weight"))
			{
				AccumulateAngle += 25.f;
			}
			else if (Actor == Player)
			{
				AccumulateAngle += SCALES_WIN_WEIGHT;
			}
		}
	}
	AngleOffset = AccumulateAngle;
	AccumulateAngle = 0.f;
	HasAngleChanged();
}

bool AScales::HasAngleChanged()
{
	if (PrevAngleOffset != AngleOffset)
	{
		if (AngleOffset == SCALES_WIN_WEIGHT || bFirstScaleChange)
		{
			bShouldPlaySequence = true;
			bFirstScaleChange = false;
		}
		bAngleChanged = true;
		PrevAngleOffset = AngleOffset;
	}
	else
	{
		bShouldPlaySequence = false;
		bAngleChanged = false;
	}
	return bAngleChanged;
}

void AScales::ChangeCameraSequence()
{
	if (Camera && CameraAngle)
	{
		if (CameraState == ECameraState::ECS_OnPlayer)
		{
			Camera->AttachToComponent(CameraAngle->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			CameraState = ECameraState::ECS_OnAngle;
		}
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, FName("ResetCamera"), Camera);
		GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 2.f, false);
		bWaitingForCamera = true;
	}
}

void AScales::ResetCamera(UCameraComponent* InCamera)
{
	InCamera->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	if (SpringArm)
	{
		InCamera->AttachToComponent(SpringArm, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		CameraState = ECameraState::ECS_OnPlayer;
		bWaitingForCamera = false;
	}
}
