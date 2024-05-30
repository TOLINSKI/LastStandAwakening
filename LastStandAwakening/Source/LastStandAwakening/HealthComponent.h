// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASTSTANDAWAKENING_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcess = "true"))
	float Health;

	class ALastStandGameMode* GameMode;

	UFUNCTION(BlueprintCallable)
	void DamageTaken(
			AActor* DamagedActor,
			float Damage,
			const UDamageType* DamageType,
			AController* Instigator,
			AActor* DamageCauser);

	UFUNCTION(BlueprintCallable)
	void FellToDeath();
		
};
