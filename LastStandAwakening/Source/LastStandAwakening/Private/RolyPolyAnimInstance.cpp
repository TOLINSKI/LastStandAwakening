// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/RolyPolyAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "../Protagonist.h"
#include "../RolyPoly.h"

void URolyPolyAnimInstance::NativeInitializeAnimation()
{
	bShouldLook = false;
	PlayerLocation = FVector::ZeroVector;

	Player = Cast<AProtagonist>(UGameplayStatics::GetPlayerPawn(this, 0));

	RolyPoly = Cast<ARolyPoly>(GetOuterUSkeletalMeshComponent()->GetOwner());
}

void URolyPolyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Player = Cast<AProtagonist>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (Player)
	{
		PlayerLocation = Player->GetActorLocation();
	}

	if (RolyPoly)
	{
		bShouldLook = RolyPoly->GetShouldLook();
	}
	else
	{
		RolyPoly = Cast<ARolyPoly>(GetOuterUSkeletalMeshComponent()->GetOwner());
	}

}