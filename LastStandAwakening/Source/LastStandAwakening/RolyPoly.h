// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RolyPoly.generated.h"

class UShaker;
class UCapsuleComponent;
class USoundBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LASTSTANDAWAKENING_API ARolyPoly : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARolyPoly();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void ShowGameWonWidget();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StandUp();

	void SetShouldStandUp(bool value);

	UFUNCTION(BlueprintCallable)
	void Reset();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayStandUpSound();

private:

	FVector StartLocation;
	FRotator StartRotation;    

	FVector BodyMeshStartLocation;
	FRotator BodyMeshStartRotation;

	bool bStartShake;

	FVector StandLocation = FVector(12192.f, 3956.f, 5.f);
	FRotator StandRotation = FRotator::ZeroRotator;

	float VInterpSpeed = 5.f;
	float RInterpSpeed = 2.f;

	bool ShouldStandUp = false;
	bool FinishStandUp = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UShaker> Shaker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RootComponent, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> Capsule;

	TObjectPtr<UStaticMeshComponent> BodyMesh;

	TObjectPtr<UStaticMeshComponent> HeadMesh;

	UPROPERTY(EditAnywhere, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> StandUpSound;
};
