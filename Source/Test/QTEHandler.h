// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Equation.h"
#include <string>
#include "InputCoreTypes.h"
#include "QTEHandler.generated.h"

UCLASS()
class TEST_API AQTEHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQTEHandler();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void GenerateEquation();
	void ValidateAnswer(EKeys keyPressed);

	UPROPERTY(EditAnywhere)
	AUIHandler* UIHandler;
private:
	Equation* currentEquation;
	std::string currentAnswer;
};
