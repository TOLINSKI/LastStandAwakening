// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trophy.generated.h"

class AScales;

UCLASS()
class LASTSTANDAWAKENING_API ATrophy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrophy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"));
	TObjectPtr<UStaticMeshComponent> Mesh;

	TObjectPtr<AScales> Scales;
};
