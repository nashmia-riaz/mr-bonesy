// Fill out your copyright notice in the Description page of Project Settings.


#include "Planet.h"

// Sets default values
APlanet::APlanet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	rotationAxis = FVector(rand() % 2, rand() % 2, rand() % 2);
}

// Called when the game starts or when spawned
void APlanet::BeginPlay()
{
	Super::BeginPlay(); 
	//FRotator MyRotator = GetOwner()->GetActorRotation(); 
	//MyRotator.Add(rotationAxis.X * UGameplayStatics::GetRealTimeSeconds(GetWorld()), rotationAxis.Y * UGameplayStatics::GetRealTimeSeconds(GetWorld()), rotationAxis.Z * UGameplayStatics::GetRealTimeSeconds(GetWorld()));
	//this->SetActorRotation(MyRotator, ETeleportType::None);
}

// Called every frame
void APlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

