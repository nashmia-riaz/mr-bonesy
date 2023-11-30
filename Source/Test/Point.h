// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlanetGenerator.h"
#include "Planet.h"
#include "GameFramework/Actor.h"
#include "Point.generated.h"

UCLASS()
class TEST_API APoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoint();
	APoint(FVector pos, bool isObs, APlanetGenerator* planetGenRef);
	void Initialize(FVector pos, bool isObs, APlanetGenerator* planetGenRef);
	FVector position;
	bool isObstacle = false;
	APlanet* planet = nullptr;

	APoint* obsPointRef = nullptr;

	//we use this to create the planet
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APlanetGenerator* planetGenerator;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
