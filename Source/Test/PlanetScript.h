// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/RotatingMovementComponent.h>
#include <Components/SphereComponent.h>
#include <GeometryCollection/GeometryCollection.h>
#include <GeometryCollection/GeometryCollectionObject.h>
#include <GeometryCollection/GeometryCollectionComponent.h>
#include <GeometryCollection/GeometryCollectionActor.h>
#include <Field/FieldSystemComponent.h>
#include "PlanetScript.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API APlanetScript : public AActor
{
	GENERATED_BODY()

public:
	APlanetScript();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UGeometryCollection*> planetGeoCollections;

	void ExplodeMesh();
	void DestroyAfterDelay(float delay);
private:
	bool isSetToBeDestroyed = false;
	
	void GenerateRandomPlanetCollection();

	URotatingMovementComponent* rotatingMovemment;
	void ApplyInitialRotation();


	USphereComponent* sphereCollision;
	void InitializeSphere();

	UGeometryCollectionComponent* planetGeoCollection;
	void InitializeGeoCollection();
	void InitializeFieldSystem();
	UFieldSystemComponent* fieldSystem;
	void Destroy();

};
