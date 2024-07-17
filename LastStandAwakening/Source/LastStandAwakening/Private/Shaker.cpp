// Fill out your copyright notice in the Description page of Project Settings.


#include "Shaker.h"

// Sets default values for this component's properties
UShaker::UShaker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bShake = false;

	ShakeFrequency = 10.f;
	ShakeAmplitude = 5.f;

	Sign = 1;

	StartedOscillation = false;
	SetR = false;
	R = 0.f;
}


// Called when the game starts
void UShaker::BeginPlay()
{
	Super::BeginPlay();

	RunningTime = 0.f;
	
	StartLocation = GetOwner()->GetActorLocation();

	StartLocation = GetOwner()->GetActorLocation();
	StartRotation = GetOwner()->GetActorRotation();
	
}


// Called every frame
void UShaker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Arg = RunningTime * 2 * UE_DOUBLE_PI * ShakeFrequency;

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
	GetOwner()->SetActorLocation(StartLocation + FVector(TransformedSin(), TransformedCos(), 0.f));
}

void UShaker::SetShakeParams(float Frequency, float Amplitude)
{
	ShakeFrequency = Frequency;
	ShakeAmplitude = Amplitude;
}

float UShaker::TransformedSin()
{
	return ShakeAmplitude * FMath::Sin(RunningTime * 2 * UE_DOUBLE_PI * ShakeFrequency);
}

float UShaker::TransformedCos()
{
	return ShakeAmplitude * FMath::Cos(RunningTime * 2 * UE_DOUBLE_PI * ShakeFrequency);
}


void UShaker::ShakeHead(float DeltaTime)
{
	float FrequencyBound = 1.f / ShakeFrequency;

	ShakeAmplitude -= 0.004f;

	RunningTime += DeltaTime;
	if (RunningTime >= FrequencyBound)
	{
		RunningTime = 0.f;
		Sign *= -1;
	}

	if (!StartedOscillation && TransformedSin() < 0.f)
	{
		StartedOscillation = true;
		UE_LOG(LogTemp, Warning, TEXT("Started Oscillation"));
	}
	
	if (StartedOscillation && (Arg < UE_HALF_PI || Arg > (UE_HALF_PI + UE_PI)))
	{
		UE_LOG(LogTemp, Error, TEXT("NOW R"));
		if (SetR == false)
		{
			R = FMath::Abs(TransformedSin());
			SetR = true;
			UE_LOG(LogTemp, Warning, TEXT("R is: %f"), R);
		}
		if (Sign * TransformedSin() > 0)
			GetOwner()->AddActorWorldRotation(FRotator(0.f, 0.f, R));
		else
			GetOwner()->AddActorWorldRotation(FRotator(0.f, 0.f, -R));
	}
	else
	{
		GetOwner()->AddActorWorldRotation(FRotator(0.f, 0.f, Sign * TransformedSin()));
	}
	// UE_LOG(LogTemp, Display, TEXT("Running Time: %f"), RunningTime);
	UE_LOG(LogTemp, Display, TEXT("Arg: %f"), Arg);

}