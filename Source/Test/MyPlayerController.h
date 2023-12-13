// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyGameManager.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<FKey> numbers = { EKeys::One, EKeys::Two, EKeys::Three, EKeys::Four, EKeys::Five, EKeys::Six, EKeys::Seven, EKeys::Eight, EKeys::Nine, EKeys::Zero };
	
	UPROPERTY(EditAnywhere)
	FString currentNumberInputString;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AMyGameManager* gameManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AUIHandler* UIHandler;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

	void KeyPressed(FKey key);

	void RegisterKey(FKey key);
};
