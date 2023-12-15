// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>
#include "Animation/WidgetAnimation.h"
#include "Equation.h"
#include "EquationWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API UEquationWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Var1;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Var2;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Answer;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Operator;


public: 
	virtual void NativeOnInitialized() override;

	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly, Category = Animations, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeIn;

	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly, Category = Animations, meta = (BindWidgetAnim))
	UWidgetAnimation* AnswerHighlight;

	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly, Category = Animations, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeOut;
	
	UPROPERTY(EditAnywhere, Transient, Category = Animations, meta = (BindWidgetAnim))
	UWidgetAnimation* CameraShake;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* TimerBar;

	FWidgetAnimationDynamicEvent OnFadeInFinished;
	FWidgetAnimationDynamicEvent OnFadeOutFinished;

	UFUNCTION()
	void ExecuteOnFadeInFinished();

	UFUNCTION()
	void ExecuteOnFadeOutFinished();

	void UpdateEquation(int x, int y, operand op);

	void UpdateAnswer(FString ans);

	void ResetUI();

	void ResetAnswer();

	void ShakeUI();
};
