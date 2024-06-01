// Fill out your copyright notice in the Description page of Project Settings.


#include "LastStandGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Protagonist.h"




void ALastStandGameMode::PawnDied(APawn* DeadPawn)
{
    APlayerController* PlayerController = Cast<APlayerController>(DeadPawn->GetController());
    if (PlayerController)
    {
        PlayerController->GameHasEnded(nullptr, false);
    }
}

void ALastStandGameMode::GameWon()
{

    AProtagonist* Player = Cast<AProtagonist>(UGameplayStatics::GetPlayerPawn(this, 0));
    if (Player)
    {
        APlayerController* PlayerController = Cast<APlayerController>(Player->GetController());
        if (PlayerController)
        {
            
            PlayerController->GameHasEnded(nullptr, true); // Should be true
        }
    }
}
