// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Point.h"
#include "GameFramework/Actor.h"
#include "MyGameManager.h"
#include <Components/SphereComponent.h>
#include "MyPlayer.generated.h"

UCLASS()
class TEST_API AMyPlayer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	AMyGameManager* gameManager;
	
private:
	void PlayerTookDamage(float damage);
	float maxHealth = 100;
	float currentHealth = 100;
};
