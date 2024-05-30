// Fill out your copyright notice in the Description page of Project Settings.


#include "LastStandGameMode.h"




void ALastStandGameMode::PawnDied(APawn* DeadPawn)
{
    APlayerController* PlayerController = Cast<APlayerController>(DeadPawn->GetController());
    if (PlayerController)
    {
        PlayerController->GameHasEnded(nullptr, false);
    }
}
