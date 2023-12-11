// Fill out your copyright notice in the Description page of Project Settings.


#include "EquationWidget.h"

void UEquationWidget::NativeOnInitialized()
{
	Super::NativeConstruct();

	OnFadeInFinished.BindDynamic(this, &UEquationWidget::ExecuteOnFadeInFinished);
	OnFadeOutFinished.BindDynamic(this, &UEquationWidget::ExecuteOnFadeOutFinished);

	BindToAnimationFinished(FadeIn, OnFadeInFinished);
	BindToAnimationFinished(FadeOut, OnFadeOutFinished);

}

void UEquationWidget::ExecuteOnFadeInFinished()
{
	PlayAnimation(AnswerHighlight, 0, 0, EUMGSequencePlayMode::Forward,1, true);
}

void UEquationWidget::ExecuteOnFadeOutFinished()
{
	StopAnimation(AnswerHighlight);
	this->SetIsEnabled(false);
}
