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

	UFUNCTION(BlueprintImplementableEvent)
	void PlaySequence();

private:
	// =========================
	bool bShouldAnimate = true;
	// =========================

	FVector StartLocation;
	FRotator StartRotation;    

	FVector BodyMeshStartLocation;
	FRotator BodyMeshStartRotation;

	bool bStartShake;
	bool bShouldLook;
	bool bDoneShaking;

	FVector StandLocation = FVector(12192.f, 3956.f, 5.f);
	FRotator StandRotation = FRotator::ZeroRotator;

	float VInterpSpeed = 5.f;
	float RInterpSpeed = 2.f;

	bool ShouldStandUp;
	bool FinishStandUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UShaker> Shaker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RootComponent, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> Capsule;

	TObjectPtr<USkeletalMeshComponent> BodyMesh;

	// TODO: Change to Skeletal Mesh Component
	TObjectPtr<UStaticMeshComponent> HeadMesh;

	UPROPERTY(EditAnywhere, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> StandUpSound;

	UPROPERTY(EditAnywhere, Category = OtherActors, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AActor> DartStepsHead;

	UPROPERTY(EditAnywhere, Category = OtherActors, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AActor> Weight;

	// Functions:
	//======================================================================

	bool PlayerInRange();

	void InitVariables();

	// Getters and Setters:
	// =====================================================================
public:

	FORCEINLINE bool GetShouldLook() { return bShouldLook; }
};
