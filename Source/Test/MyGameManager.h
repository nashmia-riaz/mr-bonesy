// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyCharacter.h"
#include "Point.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "list"
#include "MyGameManager.generated.h"

UCLASS()
class TEST_API AMyGameManager : public AActor
{
	GENERATED_BODY()
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float GetT(float t, float alpha, const FVector& p0, const FVector& p1);
	FVector CatmullRom(const FVector& p0, const FVector& p1, const FVector& p2, const FVector& p3, float t, float alpha);

public:
	// Sets default values for this actor's properties
	AMyGameManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* myPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float currentTimeInSpline= 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int currentIteration = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<APoint*> splinePoints;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APoint> splinePointBP;

	//we use this to create the planet
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APlanetGenerator* planetGenerator;

private:
	int maxRand = 300; int minRand = 50;
	FVector currentPoint = FVector(0, 0, 0);
	
	float simulationSpeed = 10;
	void CreateRandomPoint(FVector pointRef, bool shouldInitObs);
	void CreatePointOnPos(FVector pos, bool isObs);
	FVector GenerateRandomPoint(FVector previousPos);

	FVector previousPosition = FVector(0, 0, 0);
};
