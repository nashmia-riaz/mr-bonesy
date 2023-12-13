// Fill out your copyright notice in the Description page of Project Settings.


#include "QTEHandler.h"

// Sets default values
AQTEHandler::AQTEHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	currentEquation = new Equation();

}

// Called when the game starts or when spawned
void AQTEHandler::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQTEHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AQTEHandler::GenerateEquation()
{
	int varMin = 0; int varMax = 9;
	int var1 = (rand() % (varMax- varMin + 1) + varMin);
	int var2 = (rand() % (varMax - varMin + 1) + varMin);
	int opint = (rand() % (3 - 0 + 1) + 0);
	operand op = static_cast<operand>(opint);

	//we add a switch case because depending on operator, we want to modify var1 for certain conditions
	//var1 > var2 for subtraction
	//var1 % var2 = 0 for division
	switch (op) {
	case subtraction:
		varMin = var2;
		var1 = (rand() % (varMax - varMin + 1) + varMax);
		break;

	case division:
		int randMultiplier = (rand() % (varMax - varMin + 1) + varMax);
		varMin = 1;
		var2 = (rand() % (varMax - varMin + 1) + varMin);
		var1 = var2 * randMultiplier;
		break;

	}

	currentEquation->SetEquation(var1, var2, op);
	UE_LOG(LogTemp, Warning, TEXT("[QTE Handler] Generated equation"));
	
	if (!UIHandler) {
		UE_LOG(LogTemp, Error, TEXT("[QTE Handler] No UI Handler defined"));
	}
	else {
		UIHandler->UpdateEquationUI(var1, var2, op);
	}

	currentAnswer = FString::FromInt(currentEquation->GetAnswer());
}

void AQTEHandler::ValidateAnswer(FString answerGiven)
{
	
}

