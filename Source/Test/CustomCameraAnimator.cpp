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

void ACustomCameraAnimator::StartAnimation(AActor* player, APoint* obsPoint)
{
	objectToAnimate = player->GetComponentByClass<UCameraComponent>();
	float planetSize = obsPoint->planet->GetActorScale().X;

	this->prevPos = objectToAnimate->GetComponentLocation();
	this->newPos = obsPoint->position + (-obsPoint->GetActorForwardVector()*(planetSize + 100));
	this->prevRot = objectToAnimate->GetComponentRotation();
	this->newRot = UKismetMathLibrary::FindLookAtRotation(newPos, obsPoint->position);
	
	currentTimePassed = 0;
	
	USpringArmComponent* springArm = player->GetComponentByClass<USpringArmComponent>();
	springArm->bEnableCameraLag = false;

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
