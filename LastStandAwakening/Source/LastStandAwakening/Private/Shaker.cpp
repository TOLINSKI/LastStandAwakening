// Fill out your copyright notice in the Description page of Project Settings.


#include "Shaker.h"

// Sets default values for this component's properties
UShaker::UShaker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bShake = false;
}


// Called when the game starts
void UShaker::BeginPlay()
{
	Super::BeginPlay();

	RunningTime = 0.f;
	
	StartLocation = GetOwner()->GetActorLocation();
	
}


// Called every frame
void UShaker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bShake) Shake(DeltaTime);
}

void UShaker::Shake(float DeltaTime)
{
	float FrequencyBound = 1.f / ShakeFrequency;

	RunningTime += DeltaTime;
	if (RunningTime > FrequencyBound)
	{
		RunningTime = 0.f;
	}
	GetOwner()->SetActorLocation(StartLocation + FVector(TransformedSin(10.f, 5.f), TransformedCos(10.f, 5.f), 0.f));
}

float UShaker::TransformedSin(float Frequency, float Amplitude)
{
	ShakeFrequency = Frequency;
	ShakeAmplitude = Amplitude;
	return Amplitude * FMath::Sin(RunningTime * 2 * UE_DOUBLE_PI * Frequency);
}

float UShaker::TransformedCos(float Frequency, float Amplitude)
{
	ShakeFrequency = Frequency;
	ShakeAmplitude = Amplitude;
	return Amplitude * FMath::Cos(RunningTime * 2 * UE_DOUBLE_PI * Frequency);
}
