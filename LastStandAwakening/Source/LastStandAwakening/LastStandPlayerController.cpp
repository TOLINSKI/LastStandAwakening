// Fill out your copyright notice in the Description page of Project Settings.


#include "LastStandPlayerController.h"
#include "TimerManager.h"
#include "LastStandGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Protagonist.h"

void ALastStandPlayerController::BeginPlay()
{
	Super::BeginPlay();
    
}

void ALastStandPlayerController::GameHasEnded(AActor * EndGameFocus, bool bIsWinner)
{
    // Remeber To Use Super!!!!
    //Super::GameHasEnded(EndGameFocus, false); // false should be bIsWinner
    if(bIsWinner)
    {
        GetWorldTimerManager().SetTimer(RestartTimer, this,&ALastStandPlayerController::ShowGameWonWidget, WinGameDelay);
    }
    else
    {
        // GetPawn()->DisableInput(this);
        // GetWorldTimerManager().SetTimer(RestartTimer, this,&ALastStandPlayerController::RestartLevel, LooseGameDelay);
        //---------------------------------------------------------------------------------
        Cast<AProtagonist>(GetPawn())->PlayDeathSound();
        GetPawn()->Destroy();

    }
}
