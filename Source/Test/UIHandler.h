// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Subsystems/PanelExtensionSubsystem.h>
#include "HealthBarWidget.h"
#include "DangerWidget.h"
#include "EquationWidget.h"
#include "Equation.h"
#include "UIHandler.generated.h"

UCLASS()
class TEST_API AUIHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUIHandler();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UHealthBarWidget> HealthWidgetComponent_BP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHealthBarWidget* healthBarWidget;

	void SetHealth(float healthPercentage);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDangerWidget> dangerWidget_BP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDangerWidget* dangerWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UEquationWidget> equationWidget_BP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UEquationWidget* equationWidget;
	
	void TriggerDangerUI(bool enable);

	UFUNCTION()
	void ShowEquationUI();

	UFUNCTION()
	void HideEquationUI();

	void UpdateEquationUI(int var1, int var2, operand op);

	void UpdateAnswerUI(FString ans);

	void ResetEquationUI();
	
	void ResetAnswerUI();

	void UpdateEquationTimer(float timeLeftPercentage);

	void ShakeEquationUI();
};
