// Fill out your copyright notice in the Description page of Project Settings.
 #include "MyGameManager.h"
#include <ChaosBlueprint.h>

// Sets default values
AMyGameManager::AMyGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    simulationSpeed = 0.35;
    currentSpeed = simulationSpeed;
    currentTimeInSpline = 0;
}


// Called when the game starts or when spawned
void AMyGameManager::BeginPlay()
{
	Super::BeginPlay();

    currentTimeInSpline = currentIteration = 0;
    previousPosition = FVector(0, 0, 0);

    CreatePointOnPos(FVector(-100, -100, 0), FVector(-100, -100, 0), false);
    CreatePointOnPos(FVector(0, 0, 0), FVector(-100, -100, 0), false);
    CreateRandomPoint(currentPoint, false);
    CreateRandomPoint(currentPoint, false);
    CreateRandomPoint(currentPoint, false);

}

// Called every frame
void AMyGameManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!isMoving) return;

    currentTimeInSpline = currentTimeInSpline + DeltaTime * currentSpeed;

    //currentTimeInSpline = (UGameplayStatics::GetRealTimeSeconds(GetWorld()) / currentSpeed) - currentIteration;  
    FVector position = CatmullRom(splinePoints[currentIteration]->position, splinePoints[currentIteration + 1]->position, splinePoints[currentIteration + 2]->position, splinePoints[currentIteration + 3]->position, currentTimeInSpline, 0);

    //as we are reaching the end of a spline, if the 3rd point refers to an obstacle, we will slow down to a stop
    if (splinePoints[currentIteration + 2]->obsPointRef) {
        if (currentTimeInSpline > 0.5) {
            currentSpeed = FMath::Lerp(simulationSpeed, 0, (currentTimeInSpline - 0.5) / 0.5);
            UIHandler->TriggerDangerUI(true);
        }

        if (currentSpeed <= 0.005) {
            isMoving = false;
            currentSpeed = 0;
            UIHandler->TriggerDangerUI(false);
        }
    }

    //when we reach the end of a spline, generate another spline by adding a point to our spline points data structure
    if (currentTimeInSpline >= 1) {
        currentIteration++;
        currentTimeInSpline = 0;
        CreateRandomPoint(currentPoint, true);
    }
    myPlayer->SetActorLocation(position);

    FVector facingVector = position - previousPosition;
    FRotator fRotator = facingVector.Rotation();
    myPlayer->SetActorRotation(fRotator, ETeleportType::None);
    previousPosition = position;
    DrawDebugLine(GetWorld(), position, previousPosition, FColor::Red, true, -1, 0, 5);
}


void AMyGameManager::UpdateHealth(float currentHealth, float maxHealth)
{
    UIHandler->SetHealth(currentHealth / maxHealth);
}

void AMyGameManager::RecalculatePath(APoint* point)
{
    //our hit point is currentIteration + 3, so our targetted point will be currentIteration + 5
    APoint* targettedPoint = point->obsPointRef;
    if (targettedPoint) {
        APlanetScript* planet = targettedPoint->planet;
        FVector oldPosition = targettedPoint->position;

        float planetSize = planet->GetActorScale().X * 100+ 50;
        FVector facingBackwards = -targettedPoint->GetActorForwardVector();
        FVector facingRight = rand() % 2 == 1 ? targettedPoint->GetActorRightVector() : -targettedPoint->GetActorRightVector();

        //first, we need to move the point inside the planet backwards into the spline
        FVector newPosition = targettedPoint->position + (facingBackwards * planetSize);
        targettedPoint->position = newPosition;
        targettedPoint->SetActorLocation(newPosition);
        DrawDebugSphere(GetWorld(), newPosition, 5, 16, FColor::Yellow, true, 0, 0, 5);
    
        //we also need to add a point that swerves around this planet now
        newPosition = oldPosition + facingRight * planetSize;
        int insertAt = FindIndByPoint(targettedPoint) + 1;
        
        APoint* splinePoint = GetWorld()->SpawnActor<APoint>(splinePointBP, GetActorTransform());
        splinePoint->SetActorLocation(newPosition);
        splinePoint->Initialize(newPosition, false, planetGenerator);
        splinePoints.Insert(splinePoint, insertAt);
        DrawDebugSphere(GetWorld(), newPosition, 5, 16, FColor::Cyan, true, 0, 0, 5);

        //lastly, we need to add a point in front of the planet so we completely bypass it
        newPosition = oldPosition + (-facingBackwards) * planetSize;
        
        splinePoint = GetWorld()->SpawnActor<APoint>(splinePointBP, GetActorTransform());
        splinePoint->SetActorLocation(newPosition);
        splinePoint->Initialize(newPosition, false, planetGenerator);
        splinePoints.Insert(splinePoint, insertAt + 1);
        DrawDebugSphere(GetWorld(), newPosition, 5, 16, FColor::Cyan, true, 0, 0, 5);
    }
}

void AMyGameManager::CreateRandomPoint(FVector point, bool shouldInitObs)
{
    FVector newPoint = GenerateRandomPoint(point);

    bool isObstacle = false;
    if (splinePoints.Num() - lastIterationOnPlanetCreated > iterationsBeforeNextPlanet) {
        if (shouldInitObs)
            isObstacle = ((float)rand()) / (float)RAND_MAX > 0.5;
    }

    CreatePointOnPos(newPoint, point, isObstacle);

    if (isObstacle) lastIterationOnPlanetCreated = splinePoints.Num() - 1;
}

void AMyGameManager::CreatePointOnPos(FVector pos, FVector previousPos, bool isObs)
{
    APoint* splinePoint = GetWorld()->SpawnActor<APoint>(splinePointBP, GetActorTransform());
    splinePoint->SetActorLocation(pos);
    splinePoint->Initialize(pos, isObs, planetGenerator);
    splinePoints.Add(splinePoint);
    currentPoint = pos;

    FVector facingVector = pos - previousPos;
    FRotator fRotator = facingVector.Rotation();
    splinePoint->SetActorRotation(fRotator, ETeleportType::None);

    //add reference to the old point
    if (isObs && (splinePoints.Num() - 3 >= 0))
        splinePoints[splinePoints.Num() - 3]->obsPointRef = splinePoint;
    
}

FVector AMyGameManager::GenerateRandomPoint(FVector previousPos)
{
    FVector newPoint = FVector(0, 0, 0);
    FVector shouldRandomze = FVector(rand() % 2, rand() % 2, rand() % 2);
    newPoint = FVector(previousPos.X + (rand() % (maxRand - minRand + 1) + minRand) * shouldRandomze.X, previousPos.Y + (rand() % (maxRand - minRand + 1) + minRand) * shouldRandomze.Y, previousPos.Z + (rand() % (maxRand - minRand + 1) + minRand) * ((shouldRandomze.Z && shouldRandomze.X) || (shouldRandomze.Z && shouldRandomze.Y)));

    //if the new point being generated is the same as the previous, generate again
    if (newPoint == splinePoints[splinePoints.Num() - 1]->position) newPoint = GenerateRandomPoint(newPoint);

    return newPoint;

}

int AMyGameManager::FindIndByPoint(APoint* point)
{
    int ind = -1;
    for (int i = 0; i < splinePoints.Num(); i++) {
        if (splinePoints[i]->position == point->position)
        {
            ind = i;
            break;
        }
    }
    return ind;
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
