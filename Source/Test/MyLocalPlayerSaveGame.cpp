// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLocalPlayerSaveGame.h"
#include <Kismet/GameplayStatics.h>


UMyLocalPlayerSaveGame::UMyLocalPlayerSaveGame()
{
	playerSlot = highscore = 0;
	playerSaveSlotName = TEXT("PlayerSave");
}
