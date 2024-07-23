// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Protagonist.generated.h"

class UCameraComponent;
class UGrabber;


UCLASS()
class LASTSTANDAWAKENING_API AProtagonist : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AProtagonist();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintImplementableEvent)
	void PlayDeathSound();

private:

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float GamePadRotationRate = 50;

	TObjectPtr<UCameraComponent> Camera;

	TObjectPtr<UGrabber> Grabber;

public:

	FORCEINLINE TObjectPtr<UCameraComponent> GetCamera() { return Camera; }

	FORCEINLINE TObjectPtr<AActor> GetGrabbedActor();
	
};
