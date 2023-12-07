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
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AMyGameManager* gameManager;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
