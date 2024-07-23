// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"

#include "Grabber.generated.h" // Must always be last in header files!


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASTSTANDAWAKENING_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Grab();

	UFUNCTION(BlueprintCallable)
	void Release();

private:
	UPROPERTY(EditAnywhere)
	float MaxGrabDistance = 500; // Changed from 400
	UPROPERTY(EditAnywhere)
	float Damage = 0;
	UPROPERTY(EditAnywhere)
	float GrabRadius = 40; // Changed from 100
	UPROPERTY(EditAnywhere)
	float HoldDistance = 200;

	bool Grabbing = false;

	TObjectPtr<AActor> GrabbedActor;

	// Functions:
	// ==========
	UPhysicsHandleComponent* GetPhysicsHandle() const; // Function cannot cannot change the values of the object
	// i.e. Cannot change the attributes above (Damage, GrabRadius, HoldDistance etc...)
	bool GetGrabbableInReach(FHitResult& OutHitResult) const;

public:

	FORCEINLINE TObjectPtr<AActor> GetGrabbedActor() { return GrabbedActor; }
};
