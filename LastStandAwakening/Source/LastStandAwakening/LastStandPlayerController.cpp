// Fill out your copyright notice in the Description page of Project Settings.


#include "LastStandPlayerController.h"

void ALastStandPlayerController::GameHasEnded(AActor * EndGameFocus, bool bIsWinner)
{
    // Remeber To Use Super!!!!
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    UE_LOG(LogTemp, Warning, TEXT("Should Die"));
    if(bIsWinner)
    {

    }
    else
    {
        // GetPawn()->DisableInput(this);
        RestartLevel();
    }
}
