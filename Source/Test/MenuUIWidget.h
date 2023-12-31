// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include "LoadingWidget.h"
#include "MenuUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API UMenuUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CreditsButton;

	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;

	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly, Category = Animations, meta = (BindWidgetAnim))
	UWidgetAnimation* MenuToCredits;

	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly, Category = Animations, meta = (BindWidgetAnim))
	UWidgetAnimation* CreditsToMenu;

	virtual void NativeOnInitialized() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ULoadingWidget> loadingBP;

	UFUNCTION()
	void OnCreditsClick();

	UFUNCTION()
	void OnBackClick();

	UFUNCTION()
	void OnClickPlay();
};
