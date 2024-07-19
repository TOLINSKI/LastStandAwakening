// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RolyPolyAnimInstance.generated.h"

class AProtagonist;
class ARolyPoly;

/**
 * 
 */
UCLASS()
class LASTSTANDAWAKENING_API URolyPolyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:

	UPROPERTY(BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AProtagonist> Player;

	UPROPERTY(BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	FVector PlayerLocation;

	UPROPERTY(BlueprintReadOnly, Category = ControlRig, meta = (AllowPrivateAccess = "true"))
	bool bShouldLook;

	TObjectPtr<ARolyPoly> RolyPoly;
};
