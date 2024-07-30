// Fill out your copyright notice in the Description page of Project Settings.


#include "Protagonist.h"
#include "Camera/CameraComponent.h"
#include "Grabber.h"
#include "GameFramework/CharacterMovementComponent.h"
 


// Sets default values
AProtagonist::AProtagonist()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProtagonist::BeginPlay()
{
	Super::BeginPlay();

	Camera = Cast<UCameraComponent>(GetComponentByClass<UCameraComponent>());

	Grabber = GetComponentByClass<UGrabber>();
}

// Called every frame
void AProtagonist::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AProtagonist::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AProtagonist::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, 
		AController *EventInstigator, AActor *DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	//DamageToApply = FMath::Min(DamageToApply, Health);
	//Health -= DamageToApply;
	//UE_LOG(LogTemp, Display, TEXT("Damage Taken: %f, New Health: %f"), DamageToApply, Health);

    //return Health;
	return 0.f;
}

TObjectPtr<AActor> AProtagonist::GetGrabbedActor()
{
	if (Grabber)
		return Grabber->GetGrabbedActor();
	return nullptr;
}
