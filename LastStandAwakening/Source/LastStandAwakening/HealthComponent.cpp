// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "LastStandGameMode.h"
#include "LastStandPlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	// Binding DamageTaken() to UE5:OnTakeAnyDamage Event
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);

	GameMode = Cast<ALastStandGameMode>(UGameplayStatics::GetGameMode(this));
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::DamageTaken(AActor *DamagedActor, float Damage, const UDamageType *DamageType, AController *Instigator, AActor *DamageCauser)
{

}

// Called From Owner Blueprint:
void UHealthComponent::FellToDeath()
{
	APawn* Pawn = Cast<APawn>(GetOwner());
	if (GameMode)
	{
		GameMode->PawnDied(Pawn);
	}
	Health = 0;
	UE_LOG(LogTemp, Display, TEXT("Death By Carpet"));
	
}
