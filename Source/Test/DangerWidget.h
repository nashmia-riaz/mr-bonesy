// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DangerWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API UDangerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UWidgetAnimation* FadeInOutRef;
};
