// Fill out your copyright notice in the Description page of Project Settings.


#include "PlanetScript.h"

APlanetScript::APlanetScript()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void APlanetScript::BeginPlay()
{
	Super::BeginPlay();
	ApplyInitialRotation();
	InitializeSphereCollision();
	InitializeGeoCollection();
	GenerateRandomPlanetCollection();
	InitializeFieldSystem();
}

void APlanetScript::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlanetScript::GenerateRandomPlanetCollection()
{
	int minRand = 0;
	int maxRand = planetGeoCollections.Num() - 1;
	int randomPlanet = rand() % (maxRand - minRand + 1) + minRand;
	planetGeoCollection->SetRestCollection(planetGeoCollections[randomPlanet]);
	TArray<float> damage; damage.Init(1, 3);
	planetGeoCollection->SetDamageThreshold(damage);
}

void APlanetScript::ApplyInitialRotation()
{
	rotatingMovemment = this->FindComponentByClass<URotatingMovementComponent>();
	if (rotatingMovemment) {
		int minRand = 10;
		int maxRand = 25;
		FRotator rotator = FRotator(rand() % (maxRand - minRand + 1) + minRand, rand() % (maxRand - minRand + 1) + minRand, rand() % (maxRand - minRand + 1) + minRand);
		rotatingMovemment->RotationRate = rotator;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("[Planet Script] Could not find rotating movement component."));
	}
}

void APlanetScript::OnTriggerCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp) {
		//if the planet collides with player, we will shatter the planet and eventually delete the pieces
		if (OtherActor->ActorHasTag("Player"))
		{
			ExplodeMesh();
		}
		else if (OtherActor->ActorHasTag("PlayerOuter")) {
			DestroyAfterDelay(30);
		}
	}
}

void APlanetScript::InitializeSphereCollision()
{
	sphereCollision = this->FindComponentByClass<USphereComponent>();
	if (sphereCollision) {
		sphereCollision->OnComponentBeginOverlap.AddDynamic(this, &APlanetScript::OnTriggerCollision);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("[Planet Script] Could not find sphere collision component."));
	}
}

void APlanetScript::InitializeGeoCollection()
{
	planetGeoCollection = this->FindComponentByClass<UGeometryCollectionComponent>();
}

void APlanetScript::InitializeFieldSystem()
{
	fieldSystem = this->FindComponentByClass<UFieldSystemComponent>();
}

void APlanetScript::ExplodeMesh()
{
	if (!planetGeoCollection) {
		UE_LOG(LogTemp, Warning, TEXT("[Planet] Could not find the planet geo collection or field system ref"));
		return;
	}
	if (planetGeoCollection && fieldSystem) {
		planetGeoCollection->SetSimulatePhysics(true);
		/*UPrimitiveComponent* root = (UPrimitiveComponent*) planetGeoCollection;
		root->SetSimulatePhysics(true);*/
		//planetGeoCollection->SetSimulatePhysics(true);

		//apply an external strain to break the object
		URadialFalloff* radialFalloff = NewObject<URadialFalloff>();
		radialFalloff->SetRadialFalloff(10, 0, 1, 0, sphereCollision->GetScaledSphereRadius(), sphereCollision->GetComponentLocation(), Field_FallOff_None);
		fieldSystem->ApplyPhysicsField(true, Field_ExternalClusterStrain, NULL, radialFalloff);
		
		//apply a further force to move the shards
		URadialVector* radialVector = NewObject<URadialVector>();
		radialVector->SetRadialVector(100, sphereCollision->GetComponentLocation());
		fieldSystem->ApplyPhysicsField(true, Field_LinearVelocity, NULL, radialVector);

		//create an explosion emitter
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionParticleEmitter, FTransform(GetActorLocation()), true, EPSCPoolMethod::None, true);
		DestroyAfterDelay(30);
	}
}

void APlanetScript::DestroyAfterDelay(float delay)
{
	if (isSetToBeDestroyed) return;

	isSetToBeDestroyed = true;
	FTimerHandle unusedHandle;
	GetWorldTimerManager().SetTimer(unusedHandle, this, &APlanetScript::Destroy, delay, false);
}

void APlanetScript::Destroy()
{
	Super::Destroy();
}
