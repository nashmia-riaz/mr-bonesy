// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

void AMyPlayerController::BeginPlay()
{
	EnableInput(this);
    
    TArray<AActor*> ActorsToFind;
    if (UWorld* World = GetWorld())
    {
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), ActorsToFind);
    }
	for (AActor* TargetActor : ActorsToFind)
	{
		if (TargetActor->ActorHasTag("GameManager"))
		{
			gameManager = (AMyGameManager*) TargetActor;
		}
		else if (TargetActor->ActorHasTag("UIHandler")) {
			UIHandler = (AUIHandler*)TargetActor;
		}

		if (UIHandler && gameManager) {
			break;
		}
    }
}

void AMyPlayerController::Tick(float DeltaTime)
{
	if (WasInputKeyJustPressed(EKeys::AnyKey)) {
		
	}
}

void AMyPlayerController::KeyPressed(FKey key)
{
	FKey keyExpected;

	//first we will check the input size with expected answer, only keep registering if string sizes is less or equal
	if (gameManager->QTEHandler->currentAnswer.Len() > currentNumberInputString.Len()) {
		//if the key pressed is one of the numbers
		if (numbers.Contains(key)) {
			RegisterKey(key);
			UE_LOG(LogTemp, Log, TEXT("Key Pressed: %s"), *key.GetFName().ToString());
		}

		//if both strings are now equal
		if (gameManager->QTEHandler->currentAnswer.Len() == currentNumberInputString.Len()) {
			gameManager->QTEHandler->ValidateAnswer(currentNumberInputString);
			UE_LOG(LogTemp, Log, TEXT("Validating answers: %s with %s"),*gameManager->QTEHandler->currentAnswer, *currentNumberInputString);
		}
	}
}

void AMyPlayerController::RegisterKey(FKey keyPressed)
{
	if (keyPressed == EKeys::One) {
		currentNumberInputString += "1";
	}
	else if (keyPressed == EKeys::Two) {
		currentNumberInputString += "2";
	}
	else if (keyPressed == EKeys::Three) {
		currentNumberInputString += "3";
	}
	else if (keyPressed == EKeys::Four) {
		currentNumberInputString += "4";
	}
	else if (keyPressed == EKeys::Five) {
		currentNumberInputString += "5";
	}
	else if (keyPressed == EKeys::Six) {
		currentNumberInputString += "6";
	}
	else if (keyPressed == EKeys::Seven) {
		currentNumberInputString += "7";
	}
	else if (keyPressed == EKeys::Eight) {
		currentNumberInputString += "8";
	}
	else if (keyPressed == EKeys::Nine) {
		currentNumberInputString += "9";
	}
	else if (keyPressed == EKeys::Zero) {
		currentNumberInputString += "0";
	}

	UIHandler->UpdateAnswerUI(currentNumberInputString);
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("AnyKeyPressed", EInputEvent::IE_Pressed, this, &AMyPlayerController::KeyPressed);
}

