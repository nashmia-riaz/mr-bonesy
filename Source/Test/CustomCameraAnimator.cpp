// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCameraAnimator.h"

// Sets default values
ACustomCameraAnimator::ACustomCameraAnimator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	currentTimePassed = 0;
}

// Called when the game starts or when spawned
void ACustomCameraAnimator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACustomCameraAnimator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isAnimating) Animate(DeltaTime);
}

void ACustomCameraAnimator::StartAnimation(FVector prevPosition, FRotator prevRotator, FVector targetLocation, FRotator finalRot, USceneComponent* obj)
{
	//empty out the delegate first
	onAnimationComplete.Clear();

	this->prevPos = prevPosition;
	this->newPos = targetLocation;
	this->prevRot = prevRotator;
	this->newRot = finalRot;
	
	currentTimePassed = 0;
	
	objectToAnimate = obj;

	isAnimating = true;
}

void ACustomCameraAnimator::Animate(float deltaTime)
{
	FVector currentPos = FMath::Lerp(prevPos, newPos, currentTimePassed);
	FRotator currentRotation = FMath::Lerp(prevRot, newRot, currentTimePassed);

	objectToAnimate->SetWorldLocation(currentPos);
	objectToAnimate->SetWorldRotation(currentRotation);
	
	currentTimePassed += deltaTime;

	if (currentTimePassed > 1)
	{
		isAnimating = false;
		UE_LOG(LogTemp, Warning, TEXT("Animation complete"));
		onAnimationComplete.Broadcast();
	}
}
