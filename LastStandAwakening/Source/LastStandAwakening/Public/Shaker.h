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

	void ShakeHead(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void Shake(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shake, meta = (AllowPrivateAccess = "true"))
	bool bShake;

	void SetShakeParams(float Frequency, float Amplitude);

private:

	float RunningTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shake, meta = (AllowPrivateAccess = "true"))
	float ShakeFrequency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shake, meta = (AllowPrivateAccess = "true"))
	float ShakeAmplitude;

	FVector StartLocation;

	FRotator StartRotation;

	int32 Sign;

	bool StartedOscillation;

	bool SetR;

	float R;

	float Arg;

};
