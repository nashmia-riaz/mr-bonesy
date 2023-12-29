// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPlayer.h"
#include "PlanetScript.h"
#include "EnvironmentGenerator.generated.h"

UCLASS()
class TEST_API AEnvironmentGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnvironmentGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	AMyPlayer* player;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APlanetScript> planetBP;

	UPROPERTY(EditAnywhere)
	FVector minRand;

	UPROPERTY(EditAnywhere)
	FVector maxRand;

	void AddPlanet();

	FTimerHandle AddPlanetTimer;
	void OnPlanetTimer();

};
