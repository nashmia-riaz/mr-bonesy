// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"

void UGameOverWidget::ExecuteOnFadeInFinished()
{
	PlayAnimation(PressKeyPulse, 0, 0, EUMGSequencePlayMode::Forward, 1, false);
}

void UGameOverWidget::NativeOnInitialized()
{
	Super::NativeConstruct();

	OnFadeInFinished.BindDynamic(this, &UGameOverWidget::ExecuteOnFadeInFinished);

	BindToAnimationFinished(FadeIn, OnFadeInFinished);
}