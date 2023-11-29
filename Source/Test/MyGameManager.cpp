// Fill out your copyright notice in the Description page of Project Settings.
#include "MyGameManager.h"

// Sets default values
AMyGameManager::AMyGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


// Called when the game starts or when spawned
void AMyGameManager::BeginPlay()
{
	Super::BeginPlay();

    currentTimeInSpline = lastIncrementTime = 0;
    GeneratePointOnPos(FVector(-100, -100, 0));
    GeneratePointOnPos(FVector(0, 0, 0));
    splinePoints = { FVector(-100, -100, 0), currentPoint};
    previousPosition = FVector(0, 0, 0);
    GenerateNextPointInSplint();
    GenerateNextPointInSplint();
}

void AMyGameManager::CreateSpline() {
    if (currentIteration > 30) {
        UE_LOG(LogTemp, Warning, TEXT("Ending spline creation")); 
        return; }

    for (float i = 0; i <= 1 - 0.01; i += 0.01) {
        UE_LOG(LogTemp, Warning, TEXT("Drawing debug line"));
        FVector p1 = CatmullRom(splinePoints[splinePoints.Num() - 4], splinePoints[splinePoints.Num() - 3], splinePoints[splinePoints.Num() - 2], splinePoints[splinePoints.Num() - 1], i, 0);
        FVector p2 = CatmullRom(splinePoints[splinePoints.Num() - 4], splinePoints[splinePoints.Num() - 3], splinePoints[splinePoints.Num() - 2], splinePoints[splinePoints.Num() - 1], i + 0.01, 0);
        DrawDebugLine(GetWorld(), p1, p2, FColor::Red, true, -1, 0, 5);
    }
    currentIteration++;
    GenerateNextPointInSplint();
    CreateSpline();
}

// Called every frame
void AMyGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    currentTimeInSpline = UGameplayStatics::GetRealTimeSeconds(GetWorld()) / simulationSpeed - lastIncrementTime;  
    FVector position = CatmullRom(splinePoints[splinePoints.Num() - 4], splinePoints[splinePoints.Num() - 3], splinePoints[splinePoints.Num() - 2], splinePoints[splinePoints.Num() - 1], currentTimeInSpline, 0);
    
    //when we reach the end of a spline, generate another spline by adding a point to our spline points data structure
    if (currentTimeInSpline >= 1) {
        lastIncrementTime += currentTimeInSpline;
        GenerateNextPointInSplint();
    }
    myPlayer->SetActorLocation(position);

    FVector facingVector = position - previousPosition;
    FRotator fRotator = facingVector.Rotation();
    myPlayer->SetActorRotation(fRotator, ETeleportType::None);
    previousPosition = position;
    DrawDebugLine(GetWorld(), position, previousPosition, FColor::Red, true, -1, 0, 5);
}

FVector AMyGameManager::GenerateRandomPoint(FVector point)
{
    FVector newPoint = FVector(0, 0, 0);
    FVector shouldRandomze = FVector(rand() % 2, rand() % 2, rand() % 2);
    newPoint = FVector(point.X + (rand() % (maxRand - minRand + 1) + minRand) * shouldRandomze.X, point.Y + (rand() % (maxRand - minRand + 1) + minRand) * shouldRandomze.Y, point.Z + (rand() % (maxRand - minRand + 1) + minRand) * shouldRandomze.Z);
    
    //if the new point being generated is the same as the previous, generate again
    if (newPoint == splinePoints[splinePoints.Num() - 1]) newPoint = GenerateRandomPoint(newPoint);

    AActor* splinePoint = GetWorld()->SpawnActor<AActor>(splinePointBP, GetActorTransform());
    splinePoint->SetActorLocation(newPoint);
    return newPoint;
}

void AMyGameManager::GeneratePointOnPos(FVector pos)
{
    AActor* splinePoint = GetWorld()->SpawnActor<AActor>(splinePointBP, GetActorTransform());
    splinePoint->SetActorLocation(pos);
    splinePoints.Add(pos);
}

void AMyGameManager::GenerateNextPointInSplint()
{
    FVector newPoint = GenerateRandomPoint(currentPoint);
    splinePoints.Add(newPoint);
    currentPoint = newPoint;
}

float AMyGameManager::GetT(float t, float alpha, const FVector& p0, const FVector& p1)
{
    auto d = p1 - p0;
    float a = d | d; // Dot product
    float b = FMath::Pow(a, alpha * .5f);
    return (b + t);
}

FVector AMyGameManager::CatmullRom(const FVector& p0, const FVector& p1, const FVector& p2, const FVector& p3, float t, float alpha)
{
    float t0 = 0.0f;
    float t1 = GetT(t0, alpha, p0, p1);
    float t2 = GetT(t1, alpha, p1, p2);
    float t3 = GetT(t2, alpha, p2, p3);
    t = FMath::Lerp(t1, t2, t);
    FVector A1 = (t1 - t) / (t1 - t0) * p0 + (t - t0) / (t1 - t0) * p1;
    FVector A2 = (t2 - t) / (t2 - t1) * p1 + (t - t1) / (t2 - t1) * p2;
    FVector A3 = (t3 - t) / (t3 - t2) * p2 + (t - t2) / (t3 - t2) * p3;
    FVector B1 = (t2 - t) / (t2 - t0) * A1 + (t - t0) / (t2 - t0) * A2;
    FVector B2 = (t3 - t) / (t3 - t1) * A2 + (t - t1) / (t3 - t1) * A3;
    FVector C = (t2 - t) / (t2 - t1) * B1 + (t - t1) / (t2 - t1) * B2;
    return C;
}
