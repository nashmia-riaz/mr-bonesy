// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MyLocalPlayerSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API UMyLocalPlayerSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere)
	int highscore;

	UPROPERTY(VisibleAnywhere)
	int32 playerSlot;

	UPROPERTY(VisibleAnywhere)
	FString playerSaveSlotName;

	UMyLocalPlayerSaveGame();
};
