// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvironmentGenerator.h"

// Sets default values
AEnvironmentGenerator::AEnvironmentGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnvironmentGenerator::BeginPlay()
{
	Super::BeginPlay();

	if(!player)
	{
		UE_LOG(LogTemp, Error, TEXT("[Environment Generator] Could not find player reference."));
	}
	else {
		for (int i = 0; i < 10; i++) {
			AddPlanet();
		}

		GetWorld()->GetTimerManager().SetTimer(AddPlanetTimer, this, &AEnvironmentGenerator::OnPlanetTimer, 10.0f, true);
	}
	
}

// Called every frame
void AEnvironmentGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnvironmentGenerator::AddPlanet()
{
	APlanetScript* planet = GetWorld()->SpawnActor<APlanetScript>(planetBP, GetActorTransform());

	FVector playerPosition = player->GetActorLocation();
	float randX = (rand() % ((int)maxRand.X - (int) minRand.X + 1) + (int) minRand.X);
	float randY = (rand() % ((int)maxRand.Y - (int) minRand.Y + 1) + (int) minRand.Y);
	float randZ = (rand() % ((int)maxRand.Z - (int) minRand.Z + 1) + (int) minRand.Z);

	planet->SetActorLocation(FVector(playerPosition.X + randX, playerPosition.Y + randY, playerPosition.Z + randZ));

	USphereComponent* planetSphere = planet->FindComponentByClass<USphereComponent>();
	if (planetSphere) {
		planetSphere->SetCollisionObjectType(ECC_WorldStatic);
	}
}

void AEnvironmentGenerator::OnPlanetTimer()
{
	AddPlanet();
}
