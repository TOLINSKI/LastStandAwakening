// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Scales.generated.h"

class USkeletalMeshComponent;
class UCapsuleComponent;
class UBoxComponent;
class AProtagonist;
class ATrophy;
class ASpotLight;
class UCameraComponent;
class USpringArmComponent;
class ULevelSequence;

UCLASS()
class LASTSTANDAWAKENING_API AScales : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScales();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float WinWeight;

	UFUNCTION(BlueprintImplementableEvent)
	void PlaySequence();

private:

	// Variables:
	// ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Trigger, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> TriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> RightScaleCollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> LeftScaleCollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = OtherActors, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AProtagonist> Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OtherActors, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ATrophy> Trophy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OtherActors, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ASpotLight> TargetLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OtherActors, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AActor> Target;

	float AccumulateAngle;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float AngleOffset;

	float PrevAngleOffset;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bAngleChanged;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bHasPlayedSequence;

	bool bFirstScaleChange;

	bool bWaitingForCamera;

	enum class ECameraState
	{
		ECS_OnPlayer,
		ECS_OnAngle
	};

	ECameraState CameraState;

	// Functions:
	// ===========

	void UpdateScalesAngle();

	float GetWeight(TObjectPtr<AActor> Actor);

public:

	FORCEINLINE float GetAngleOffset() const { return AngleOffset; }
};
