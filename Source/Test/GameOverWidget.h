// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	FWidgetAnimationDynamicEvent OnFadeInFinished;
	
	UFUNCTION()
	void ExecuteOnFadeInFinished();

public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Score;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Highscore;
	
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeIn;

	UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidgetAnim))
	UWidgetAnimation* PressKeyPulse;

	virtual void NativeOnInitialized() override;
};
