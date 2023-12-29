// Fill out your copyright notice in the Description page of Project Settings.


#include "Point.h"

APoint::APoint()
{
}

// Sets default values
APoint::APoint(FVector pos, bool isObs, APlanetGenerator* planetGenRef)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	position = pos;
	isObstacle = isObs;
	planetGenerator = planetGenRef;

}

void APoint::Initialize(FVector pos, bool isObs, APlanetGenerator* planetGenRef)
{
	position = pos;
	isObstacle = isObs;
	planetGenerator = planetGenRef;

	if (isObstacle) {
		planet = planetGenerator->SpawnPlanet();
		planet->SetActorLocation(position);
		float randScale = ((float(rand()) / float(RAND_MAX)) * (1.25 - 0.75)) + 0.75;
		planet->SetActorScale3D(FVector(randScale, randScale, randScale));
	}
}

// Called when the game starts or when spawned
void APoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

