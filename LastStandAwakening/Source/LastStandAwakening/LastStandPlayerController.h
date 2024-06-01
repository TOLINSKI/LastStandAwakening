// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LastStandPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LASTSTANDAWAKENING_API ALastStandPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float WinGameDelay = 5.f;

	UPROPERTY(EditAnywhere)
	float LooseGameDelay = 0.1;

	FTimerHandle RestartTimer;

	

};
