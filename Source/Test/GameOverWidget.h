// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Score;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Highscore;
	
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeIn;
};
