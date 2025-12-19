// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	enemyDataTable = TSoftObjectPtr<UDataTable>(FSoftObjectPath(TEXT("/Game/Data/DT_Enemies.DT_Enemies")));
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer
	(
		enemyTimer,
		this,
		&AEnemySpawner::SpawnEnemy,
		TimeBetweenSpawns,
		true
	);
	
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::SpawnEnemy()
{
	UDataTable* table = enemyDataTable.LoadSynchronous();
	FST_EnemyDataRow* row = table->FindRow<FST_EnemyDataRow>("Purple", TEXT("Lookup"));;
	int enemyType = rand() % 3;


	if (SpawnsTillBoss >= 50)
	{
		row = table->FindRow<FST_EnemyDataRow>("Purple", TEXT("Lookup"));
		
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, FString::Printf(TEXT("Bool value: %s"), row ? TEXT("true") : TEXT("false")));
		AEnemy_Base* bossEnemy = GetWorld()->SpawnActor<AEnemy_Base>(GetRandomPointOutsideRadius(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), 800, 1500), FRotator(0,0,0));
		bossEnemy->Initalise(row);

		SpawnsTillBoss = 0;
	}


	switch (enemyType)
	{
	default:
		break;

	case 0:		//Spawning red
		row = table->FindRow<FST_EnemyDataRow>("Red", TEXT("Lookup"));
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, FString::Printf(TEXT("Bool value: %s"), row ? TEXT("true") : TEXT("false")));
		break;
	case 1:		//Spawning blue
		row = table->FindRow<FST_EnemyDataRow>("Blue", TEXT("Lookup"));
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, FString::Printf(TEXT("Bool value: %s"), row ? TEXT("true") : TEXT("false")));
		break;
	case 2:		//Spawning green
		row = table->FindRow<FST_EnemyDataRow>("Green", TEXT("Lookup"));
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, FString::Printf(TEXT("Bool value: %s"), row ? TEXT("true") : TEXT("false")));
		break;
	}

	int numToSpawn = rand() % 8 + 3;

	for (int x = 0; x < numToSpawn; x++)
	{
		AEnemy_Base* normalEnemy = GetWorld()->SpawnActor<AEnemy_Base>(GetRandomPointOutsideRadius(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), 800, 1500), FRotator(0, 0, 0));
		if(IsValid(normalEnemy))
			normalEnemy->Initalise(row);
	}
		
	SpawnsTillBoss += numToSpawn;
}



FVector AEnemySpawner::GetRandomPointOutsideRadius(const FVector& Origin, float Radius, float MaxDistance)
{
	// Random angle
	float Angle = FMath::RandRange(0.f, 2.f * PI);

	// Random distance between Radius and MaxDistance
	float Distance = FMath::RandRange(Radius, MaxDistance);

	float X = FMath::Cos(Angle) * Distance;
	float Y = FMath::Sin(Angle) * Distance;

	return Origin + FVector(X, Y, 0.f);
}
