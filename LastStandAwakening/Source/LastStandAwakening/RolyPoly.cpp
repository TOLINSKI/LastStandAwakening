// Fill out your copyright notice in the Description page of Project Settings.


#include "RolyPoly.h"
#include "Kismet/GameplayStatics.h"
#include "LastStandGameMode.h"

// Sets default values
ARolyPoly::ARolyPoly()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARolyPoly::BeginPlay()
{
	Super::BeginPlay();

	ShouldStandUp = false;
}

// Called every frame
void ARolyPoly::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ShouldStandUp)
	{
		StandUp();
	}

}

void ARolyPoly::StandUp()
{
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	FRotator ActorRotation = GetActorRotation();

	if (!ActorRotation.Equals(StandRotation, 1))
	{
		SetActorRotation(FMath::RInterpTo(
			ActorRotation, 
			StandRotation,
			DeltaTime,
			RInterpSpeed));
	}
	else
	{
		ShouldStandUp = false;	
		ALastStandGameMode* GameMode = GetWorld()->GetAuthGameMode<ALastStandGameMode>();
		if (GameMode)
		{
			GameMode->GameWon();
		}
		ShowGameWonWidget();
	}

	if (FVector::Dist(GetActorLocation(), StandLocation) > 1)
	{
		SetActorLocation(FMath::VInterpTo(
			GetActorLocation(), 
			StandLocation,
			DeltaTime,
			VInterpSpeed));
	}
}

void ARolyPoly::SetShouldStandUp(bool value)
{
	ShouldStandUp = value;
}

// void ARolyPoly::ShowGameWonWidget()
// {
// 	TSubclassOf<UGameWonWidget> GameWonWidgetClass;	
// 	UGameWonWidget* GameWonTextWidget;

// 	if(GameWonWidgetClass)
// 	{
// 		if(!GameWonTextWidget)
// 		{
// 			GameWonTextWidget = Cast<UGameWonWidget>(CreateWidget(this, GameWonWidgetClass));
// 			UE_LOG(LogTemp, Display, TEXT("Widget Created!"));
// 		}
// 	}	
// }

