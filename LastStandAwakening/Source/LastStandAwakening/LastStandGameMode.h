// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LastStandGameMode.generated.h"

/**
 * 
 */
UCLASS()
class LASTSTANDAWAKENING_API ALastStandGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	void PawnDied(APawn* DeadPawn);

	void GameWon();

};
