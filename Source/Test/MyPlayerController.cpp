// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

void AMyPlayerController::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Setup input"));
	EnableInput(this);
    
    TArray<AActor*> ActorsToFind;
    if (UWorld* World = GetWorld())
    {
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyGameManager::StaticClass(), ActorsToFind);
    }
	for (AActor* GameManagerActor : ActorsToFind)
	{
		if (GameManagerActor->ActorHasTag("GameManager"))
		{
			gameManager = (AMyGameManager*) GameManagerActor;
			break;
		}
    }
}

void AMyPlayerController::Tick(float DeltaTime)
{
	if (WasInputKeyJustPressed(EKeys::T)) {
		gameManager->RecalculatePath();
		gameManager->PanToPlayer();
	}
	if (WasInputKeyJustPressed(EKeys::R)) {
		gameManager->PanToPlayer();
	}
}
