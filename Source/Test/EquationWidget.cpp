﻿// Fill out your copyright notice in the Description page of Project Settings.


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

void UEquationWidget::UpdateEquation(int x, int y, operand op)
{
	Var1->SetText(FText::FromString(FString::FromInt(x)));
	Var2->SetText(FText::FromString(FString::FromInt(y)));
	
	FString opString = "";
	switch (op) {
	case addition:
		opString = "+";
		break;

	case subtraction:
		opString = "-";
		break;

	case multiplication:
		opString = "x";
		break;

	case division:
		opString = UTF8_TO_TCHAR(u8"÷");
		break;
	}

	Operator->SetText(FText::FromString(opString));

	UE_LOG(LogTemp, Warning, TEXT("[Equation Widget] updating equation UI"));
}
