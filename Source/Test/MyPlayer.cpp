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
			UE_LOG(LogTemp, Warning, TEXT("Hit spline point: %f, %f, %f"), OtherActor->GetActorLocation().X, OtherActor->GetActorLocation().Y, OtherActor->GetActorLocation().Z);
		}
	}
}
