// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	if (!gameManager) UE_LOG(LogTemp, Error, TEXT("[Player] Please add reference to game manager object"));

	camera = this->FindComponentByClass<UCameraComponent>();
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyPlayer::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp) {
		if (OtherActor->ActorHasTag("SplinePoint"))
		{
			APoint* point = (APoint*) OtherActor;
			UE_LOG(LogTemp, Log, TEXT("[Player] Hit point (%f, %f, %f) has obstacle reference %d"), point->position.X, point->position.Y, point->position.Z, point->obsPointRef != nullptr);
		}
		else if (OtherActor->ActorHasTag("Planet")) {
			//create an explosion emitter
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionParticleEmitter, FTransform(GetActorLocation()), true, EPSCPoolMethod::None, true);
			//register damage
			PlayerTookDamage(10);

			//if player is still alive, destroy the planet
			if (currentHealth > 0)
			{
				APlanetScript* planet = (APlanetScript*)OtherActor;
				planet->ExplodeMesh();
			}
			//destroy the player if death
			else {
				ExplodePlayer();
			}
		}
	}
}

//we have an outer collider on the player that we use to destroy planets we managed to avoid (after 30s)
void AMyPlayer::OnOuterPlayerCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Planet")) {
		APlanetScript* planet = (APlanetScript*)OtherActor;
		planet->DestroyAfterDelay(30);
	}
}

//function for registering damage
void AMyPlayer::PlayerTookDamage(float damage)
{
	currentHealth -= damage;
	if (currentHealth <= 0) { 
		currentHealth = 0; 
	}
	
	gameManager->UpdateHealth(currentHealth, maxHealth);
}

void AMyPlayer::RecalculateRoute(APoint* currentPoint)
{
	gameManager->RecalculatePath(currentPoint);
}

//to explode the player, we set it's meshes to invisible and spawn the shattered player blueprint
void AMyPlayer::ExplodePlayer()
{
	UChildActorComponent* UFO = FindComponentByTag<UChildActorComponent>(FName(TEXT("UFO")));
	UChildActorComponent* cat = FindComponentByTag<UChildActorComponent>(FName(TEXT("Cat")));
	if (UFO && cat) {
		UFO->SetVisibility(false); cat->SetVisibility(false);
	}

	AActor* explodedPlayer = GetWorld()->SpawnActor<AActor>(PlayerShatteredBP, GetActorTransform());
	explodedPlayer->SetActorRotation(GetActorRotation(), ETeleportType::None);
	explodedPlayer->SetActorLocation(GetActorLocation());
}

