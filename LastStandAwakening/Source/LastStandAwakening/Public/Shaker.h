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

	FVector StartLocation;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	float TransformedSin(float Frequency = 0.5f, float Amplitude = 10.f);

	float TransformedCos(float Frequency = 0.5f, float Amplitude = 10.f);


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	float RunningTime;

	float ShakeFrequency;

	float ShakeAmplitude;
};
