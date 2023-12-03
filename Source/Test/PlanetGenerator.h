// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlanetScript.h"
#include <GeometryCollection/GeometryCollectionObject.h>
#include "PlanetGenerator.generated.h"
UCLASS()
class TEST_API APlanetGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlanetGenerator();

	UPROPERTY(EditAnywhere)
	TSubclassOf<APlanetScript> planet;

	APlanetScript* SpawnPlanet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
