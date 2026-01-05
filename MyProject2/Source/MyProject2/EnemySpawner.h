// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Characters/Enemy_Base.h"
#include "ST_Enemy.h"
#include "EnemySpawner.generated.h"

UCLASS()
class MYPROJECT2_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void SpawnEnemy();
	FVector GetRandomPointOutsideRadius(const FVector& Origin, float Radius, float MaxDistance);

	float TimeBetweenSpawns = 3.0f;
	FTimerHandle enemyTimer;

	uint8 SpawnsTillBoss= 0;

	TSoftObjectPtr<UDataTable> enemyDataTable;
	
};
