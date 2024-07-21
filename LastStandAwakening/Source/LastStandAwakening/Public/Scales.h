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

	UFUNCTION(BlueprintImplementableEvent)
	void MoveCamera(FVector Location);

private:

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ATrophy> Trophy;

	float AccumulateAngle;

	float AngleOffset;

public:

	FORCEINLINE float GetAngleOffset() const { return AngleOffset; }
};
