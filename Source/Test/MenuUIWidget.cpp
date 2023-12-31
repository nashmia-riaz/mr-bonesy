// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuUIWidget.h"
#include <Kismet/GameplayStatics.h>

void UMenuUIWidget::NativeOnInitialized() {
	StartButton->OnClicked.AddDynamic(this, &UMenuUIWidget::OnClickPlay);
	CreditsButton->OnClicked.AddDynamic(this, &UMenuUIWidget::OnCreditsClick);
	BackButton->OnClicked.AddDynamic(this, &UMenuUIWidget::OnBackClick);
}

void UMenuUIWidget::OnCreditsClick()
{
	PlayAnimation(MenuToCredits, 0, 1, EUMGSequencePlayMode::Forward, 1, false);
}

void UMenuUIWidget::OnBackClick()
{
	PlayAnimation(CreditsToMenu, 0, 1, EUMGSequencePlayMode::Forward, 1, false);
}

void UMenuUIWidget::OnClickPlay()
{
	UGameplayStatics::OpenLevel(GetWorld(), "NewMap");
	UE_LOG(LogTemp, Warning, TEXT("Loading game"));

	ULoadingWidget* loading = CreateWidget<ULoadingWidget>(GetWorld(), loadingBP);
	loading->SetIsEnabled(true);
	loading->RenderOpacity = 0;
	loading->AddToViewport();
	loading->PlayAnimation(loading->FadeIn, 0, 1, EUMGSequencePlayMode::Forward, 1, false);
}
