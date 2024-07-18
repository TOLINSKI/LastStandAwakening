// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Shaker.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASTSTANDAWAKENING_API UShaker : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShaker();

	float TransformedSin();

	float TransformedCos();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ShakeRoly(TObjectPtr<UStaticMeshComponent> BodyMesh);

	UFUNCTION(BlueprintCallable)
	void Shake(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shake, meta = (AllowPrivateAccess = "true"))
	bool bShake;

	void SetShakeParams(float Frequency, float Amplitude);

	void Reset();

private:

	float RunningTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shake, meta = (AllowPrivateAccess = "true"))
	float ShakeFrequency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shake, meta = (AllowPrivateAccess = "true"))
	float ShakeAmplitude;

	FVector StartLocation;

	FRotator StartRotation;

	/**
	* Head Shake Stuff
	*/

	float Arg;

	float ExpHelper;

	FVector BodyMeshStartLocation;

	bool bSetBodyMeshStart;

};
