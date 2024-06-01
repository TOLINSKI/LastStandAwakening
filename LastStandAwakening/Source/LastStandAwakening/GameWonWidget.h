// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameWonWidget.generated.h"

/**
 * 
 */
UCLASS()
class LASTSTANDAWAKENING_API UGameWonWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
};
