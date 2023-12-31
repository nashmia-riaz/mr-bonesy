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

	if (!dangerWidget_BP || !equationWidget_BP)
	{
		UE_LOG(LogTemp, Error, TEXT("[UI HANDLER] Can't initialize UI handler. Please add UI references."));
		return;
	}
	/*healthBarWidget = CreateWidget<UHealthBarWidget>(GetWorld(), HealthWidgetComponent_BP);
	healthBarWidget->AddToViewport();*/

	//transition from loading screen
	ULoadingWidget* loading = CreateWidget<ULoadingWidget>(GetWorld(), loading_BP);
	loading->RenderOpacity = 1;
	loading->AddToViewport();
	loading->SetIsEnabled(true);
	loading->PlayAnimation(loading->FadeOut, 0, 1, EUMGSequencePlayMode::Forward, 1, false);

	dangerWidget = CreateWidget<UDangerWidget>(GetWorld(), dangerWidget_BP);
	dangerWidget->AddToViewport();
	dangerWidget->SetIsEnabled(false);

	equationWidget = CreateWidget<UEquationWidget>(GetWorld(), equationWidget_BP);
	equationWidget->AddToViewport();
	equationWidget->SetIsEnabled(false);
	ResetEquationUI();

	scoreWidget = CreateWidget<UScoreWidget>(GetWorld(), scoreWidget_BP);
	scoreWidget->AddToViewport();
	scoreWidget->SetIsEnabled(true);

	gameOverWidget = CreateWidget <UGameOverWidget>(GetWorld(), gameOver_BP);
	gameOverWidget->SetIsEnabled(false);
	gameOverWidget->AddToViewport();

	damageWidget = CreateWidget<UDamageWidget>(GetWorld(), damage_BP);
	damageWidget->SetIsEnabled(true);
	damageWidget->AddToViewport();
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

void AUIHandler::ShowEquationUI()
{
	equationWidget->SetIsEnabled(true);
	equationWidget->PlayAnimation(equationWidget->FadeIn, 0, 1, EUMGSequencePlayMode::Forward, 1, false);
	
}

void AUIHandler::HideEquationUI()
{
	equationWidget->PlayAnimation(equationWidget->FadeOut, 0, 1, EUMGSequencePlayMode::Forward, 1, true);
}

void AUIHandler::UpdateEquationUI(int var1, int var2, operand op)
{
	equationWidget->UpdateEquation(var1, var2, op);
}

void AUIHandler::UpdateAnswerUI(FString ans)
{
	equationWidget->UpdateAnswer(ans);
}

void AUIHandler::ResetEquationUI()
{
	equationWidget->ResetUI();
	equationWidget->TimerBar->Percent = 1;
}

void AUIHandler::ResetAnswerUI()
{
	equationWidget->ResetAnswer();
}

void AUIHandler::UpdateEquationTimer(float timeLeftPercentage)
{
	equationWidget->TimerBar->SetPercent(timeLeftPercentage);
}

void AUIHandler::ShakeEquationUI()
{
	equationWidget->ShakeUI();
}

void AUIHandler::UpdateScore(int score)
{
	scoreWidget->scoreText->SetText(FText::FromString("SCORE: " + FString::FromInt(score)));
}

void AUIHandler::TriggerGameOver(int score, int highscore) {
	gameOverWidget->SetIsEnabled(true);
	gameOverWidget->Score->SetText(FText::FromString("SCORE: " + FString::FromInt(score)));
	gameOverWidget->Highscore->SetText(FText::FromString("HIGHSCORE: " + FString::FromInt(highscore)));
	gameOverWidget->PlayAnimation(gameOverWidget->FadeIn, 0, 1, EUMGSequencePlayMode::Forward, 1, false);
}

void AUIHandler::TriggerDamageUI()
{
	damageWidget->PlayAnimation(damageWidget->FadeInOut, 0, 1, EUMGSequencePlayMode::Forward, 1, false);
}
