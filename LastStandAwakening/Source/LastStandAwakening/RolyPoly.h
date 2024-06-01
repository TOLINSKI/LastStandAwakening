// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RolyPoly.generated.h"

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


private:

	FVector StandLocation = FVector(12146, 3098, 127);
	FRotator StandRotation = FRotator(0 ,180 , 0);

	float VInterpSpeed = 5.f;
	float RInterpSpeed = 2.f;

	bool ShouldStandUp = false;
	bool FinishStandUp = false;
	
};
