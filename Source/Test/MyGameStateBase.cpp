// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameStateBase.h"

void AMyGameStateBase::BeginPlay()
{
   /* APlayerController* playerController = GEngine->GetFirstLocalPlayerController(GEngine->GetWorld());
    this->myCharacter = playerController->GetPawn();*/
    //UE_LOG(LogTemp, Warning, TEXT("[Game State] Initialized"));
}

AMyGameStateBase::AMyGameStateBase()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMyGameStateBase::Tick(float DeltaTime)
{
}
