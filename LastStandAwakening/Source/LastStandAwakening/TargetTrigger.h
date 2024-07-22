// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "TargetTrigger.generated.h"

class AProtagonist;
class AScales;

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LASTSTANDAWAKENING_API UTargetTrigger : public UBoxComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UTargetTrigger();
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:

	TObjectPtr<AProtagonist> Player;

	TObjectPtr<AScales> Scales;


	// Functions:
	// =======================================
	bool BallInTarget();

	bool GameWinConditionMet();

	bool PlayerIsOverlapping();

	void SetGameWon();

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString GameWinCondition;



public:

	FORCEINLINE FString GetGameWinCondition() { return GameWinCondition; }

	
};
