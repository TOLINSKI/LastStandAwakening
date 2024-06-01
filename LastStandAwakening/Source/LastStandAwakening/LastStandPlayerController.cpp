// Fill out your copyright notice in the Description page of Project Settings.


#include "LastStandPlayerController.h"
#include "TimerManager.h"

void ALastStandPlayerController::BeginPlay()
{
	Super::BeginPlay();
    
}

void ALastStandPlayerController::GameHasEnded(AActor * EndGameFocus, bool bIsWinner)
{
    // Remeber To Use Super!!!!
    //Super::GameHasEnded(EndGameFocus, false); // false should be bIsWinner
    UE_LOG(LogTemp, Warning, TEXT("GAME HAS ENDED!"));
    if(bIsWinner)
    {
        GetWorldTimerManager().SetTimer(RestartTimer, this,&ALastStandPlayerController::RestartLevel, WinGameDelay);
    }
    else
    {
        // GetPawn()->DisableInput(this);
        GetWorldTimerManager().SetTimer(RestartTimer, this,&ALastStandPlayerController::RestartLevel, LooseGameDelay);
    }
}
