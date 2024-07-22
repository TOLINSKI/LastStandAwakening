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

	UFUNCTION(BlueprintImplementableEvent)
	void OnScalesChange();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void MoveCamera(FVector Location);

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AProtagonist> Player;

	TObjectPtr<AActor> CameraAngle;

	TObjectPtr<USpringArmComponent> SpringArm;

	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ATrophy> Trophy;

	TObjectPtr<ASpotLight> TargetLight;

	float AccumulateAngle;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float AngleOffset;

	float PrevAngleOffset;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bAngleChanged;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bShouldPlaySequence;

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

	bool HasAngleChanged();

	UFUNCTION(BlueprintCallable)
	void ResetCamera(UCameraComponent* Camera);

	UFUNCTION()
	void ChangeCameraSequence();

public:

	FORCEINLINE float GetAngleOffset() const { return AngleOffset; }
};
