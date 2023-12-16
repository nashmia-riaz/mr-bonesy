// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Point.h"
#include "MyGameManager.h"
#include <Components/SphereComponent.h>
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "InputCoreTypes.h"
#include <GameFramework/SpringArmComponent.h>
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

	UFUNCTION(BlueprintCallable)
	void OnOuterPlayerCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	AMyGameManager* gameManager;

	UPROPERTY(EditAnywhere)
	UParticleSystem* explosionParticleEmitter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> PlayerShatteredBP;
	
private:
	void PlayerTookDamage(float damage);
	void RecalculateRoute(APoint* currentPoint);
	float maxHealth = 100;
	float currentHealth = 100;

	FVector previousPos = FVector(0, 0, 0);
	FVector newPos = FVector(0, 0, 0);

	UCameraComponent* camera;
	bool isAnimatingCamera = false;

	void ExplodePlayer();
};
