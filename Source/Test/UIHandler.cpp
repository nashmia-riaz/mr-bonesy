// Fill out your copyright notice in the Description page of Project Settings.


#include "UIHandler.h"

// Sets default values
AUIHandler::AUIHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUIHandler::BeginPlay()
{
	Super::BeginPlay();

	/*healthBarWidget = CreateWidget<UHealthBarWidget>(GetWorld(), HealthWidgetComponent_BP);
	healthBarWidget->AddToViewport();*/

	dangerWidget = CreateWidget<UDangerWidget>(GetWorld(), dangerWidget_BP);
	dangerWidget->AddToViewport();
	dangerWidget->SetIsEnabled(false);
}

// Called every frame
void AUIHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUIHandler::SetHealth(float healthPercentage)
{
	if (!healthBarWidget->healthbar) {
		UE_LOG(LogTemp, Error, TEXT("[UI HANDLER] Could not find the healthbar widget ref to health bar"));
		return;
	}
	healthBarWidget->healthbar->SetPercent(healthPercentage);
}

void AUIHandler::TriggerDangerUI(bool enable)
{
	//if we are calling this function repeatedly and widget is already set, return void
	if (enable == dangerWidget->bIsEnabled) return; 

	dangerWidget->SetIsEnabled(enable);
	if (enable)
	{
		if(dangerWidget->FadeInOutRef)
			dangerWidget->PlayAnimation( dangerWidget->FadeInOutRef, 0, 5, EUMGSequencePlayMode::Forward, 1, true);
	}
	else {
		dangerWidget->StopAllAnimations();
	}
}

void AUIHandler::ShowMathInputUI()
{
	UE_LOG(LogTemp, Warning, TEXT("Input UI"));
}

