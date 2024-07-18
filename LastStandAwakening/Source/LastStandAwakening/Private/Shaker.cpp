// Fill out your copyright notice in the Description page of Project Settings.


#include "Shaker.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UShaker::UShaker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	RunningTime = 0.f;

	// DroppingBook
	bShake = false;
	ShakeFrequency = 10.f;
	ShakeAmplitude = 5.f;
	
	// RolyPoly
	bSetBodyMeshStart = false;
	ExpHelper = 0.f;
}

// Called when the game starts
void UShaker::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetOwner()->GetActorLocation();
}

// Called every frame
void UShaker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float FrequencyBound = 1.f / ShakeFrequency;

	RunningTime += DeltaTime;
	if (RunningTime > FrequencyBound)
	{
		RunningTime = 0.f;
	}

	Arg = RunningTime * 2 * UE_DOUBLE_PI * ShakeFrequency;

	if (bShake) Shake(DeltaTime);
}

void UShaker::Shake(float DeltaTime)
{
	GetOwner()->SetActorLocation(StartLocation + FVector(TransformedSin(), TransformedCos(), 0.f));
}

void UShaker::SetShakeParams(float Frequency, float Amplitude)
{
	ShakeFrequency = Frequency;
	ShakeAmplitude = Amplitude;
}

float UShaker::TransformedSin()
{
	return ShakeAmplitude * FMath::Sin(Arg);
}

float UShaker::TransformedCos()
{
	return ShakeAmplitude * FMath::Cos(Arg);
}

void UShaker::ShakeRoly(TObjectPtr<UStaticMeshComponent> BodyMesh)
{
	if (!bSetBodyMeshStart)
	{
		BodyMeshStartLocation = BodyMesh->GetComponentLocation();
		bSetBodyMeshStart = true;
		RunningTime = 0.f;
	}
	if (ShakeAmplitude >= 0.f)
	{
		/**
		* Rotation
		*/
		FRotator CurrentRotation = BodyMesh->GetComponentRotation();
		FRotator Target = CurrentRotation;
		Target.Roll = -TransformedSin();

		//BodyMesh->SetWorldRotation(Target);
		BodyMesh->SetWorldRotation(FMath::RInterpTo(
			BodyMesh->GetComponentRotation(),
			Target,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			15.f
		));
		ShakeAmplitude -= 15.f * UGameplayStatics::GetWorldDeltaSeconds(this);
		
		/**
		* Location
		*/
		ExpHelper += 0.003f;
		float HalfBodySize = (ShakeAmplitude-13.f) * FMath::Pow(UE_EULERS_NUMBER, -ExpHelper);

		if (Arg <= UE_HALF_PI || (Arg >= UE_PI && Arg <= 1.5f * UE_PI ))
		{
			BodyMesh->SetWorldLocation(
				FVector(
					BodyMeshStartLocation.X, 
					BodyMeshStartLocation.Y, 
					BodyMeshStartLocation.Z + HalfBodySize * FMath::Abs(TransformedSin() / ShakeAmplitude)));
		}
		else if ((Arg > UE_HALF_PI && Arg < UE_PI) || (Arg > 1.5f * UE_PI && Arg < 2 * UE_PI))
		{
			BodyMesh->SetWorldLocation(
				FVector(
					BodyMeshStartLocation.X, 
					BodyMeshStartLocation.Y, 
					BodyMeshStartLocation.Z + HalfBodySize - HalfBodySize * FMath::Abs(TransformedCos() / ShakeAmplitude)));
		}
	}

}

void UShaker::Reset()
{
	bSetBodyMeshStart = false;
	bShake = false;
	ExpHelper = 0.f;
	RunningTime = 0.f;
}