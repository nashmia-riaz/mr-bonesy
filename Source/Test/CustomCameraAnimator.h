// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Point.h"
#include "UIHandler.h"
#include <Camera/CameraComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <GameFramework/SpringArmComponent.h>
#include "CustomCameraAnimator.generated.h"

UCLASS()
class TEST_API ACustomCameraAnimator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACustomCameraAnimator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override; 
	
	UDELEGATE(BlueprintCallable)
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnimationComplete);

	FOnAnimationComplete onAnimationComplete;
	void StartAnimation(FVector prevPosition, FRotator prevRotator, FVector targetLocation, FRotator finalRot, USceneComponent* obj);
	void Animate( float deltaTime);

	FVector GetPrevPos() { return prevPos; }
	FRotator GetPrevRot() { return prevRot; }
	FVector GetTargetPos() { return newPos; }
	FRotator GetTargetRot() { return newRot; }
private:
	bool isAnimating = false;
	FVector prevPos;
	FVector newPos;
	FRotator prevRot;
	FRotator newRot;
	float currentTimePassed = 0;
	USceneComponent* objectToAnimate;
};
