// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadingWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API ULoadingWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly, Category = Animations, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeIn;

	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly, Category = Animations, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeOut;

};
