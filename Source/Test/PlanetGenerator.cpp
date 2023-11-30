// Fill out your copyright notice in the Description page of Project Settings.


#include "PlanetGenerator.h"

// Sets default values
APlanetGenerator::APlanetGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

APlanet* APlanetGenerator::SpawnPlanet()
{
	int minRand = 0;
	int maxRand = planets.Num()-1;
	int planetToSpawn = rand() % (maxRand - minRand + 1) + minRand;
	APlanet* randomPlanet = GetWorld()->SpawnActor<APlanet>(planets[planetToSpawn], GetActorTransform());
	return randomPlanet;
}

// Called when the game starts or when spawned
void APlanetGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlanetGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
