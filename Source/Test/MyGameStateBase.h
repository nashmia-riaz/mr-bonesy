// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool hasGameStarted = false;
public:
	AMyGameStateBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	float GetT(float t, float alpha, const FVector& p0, const FVector& p1);		
	FVector CatmullRom(const FVector& p0, const FVector& p1, const FVector& p2, const FVector& p3, float t /* between 0 and 1 */, float alpha = .5f /* between 0 and 1 */);

};
