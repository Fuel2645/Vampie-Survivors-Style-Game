// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawnables/Wall.h"

// Sets default values
AWall::AWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(
		spawnTimer,
		this,
		&AWall::despawn,
		m_Duration,
		false
	);

}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWall::Initalise(int wallSegments, FVector mouseLocation, FRotator rotation)
{
	UStaticMesh* wallMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	UMaterialInterface* material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Material/MI_Black.MI_Black"));

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Wall Creation")));

	for (int x = 0; x < wallSegments; x++)
	{
		FName wallName(*FString::Printf(TEXT("wall_%d"), x));

		UStaticMeshComponent* WallSegment = NewObject<UStaticMeshComponent>(this);
		WallSegment->RegisterComponent();
		WallSegment->SetupAttachment(RootComponent);
		WallSegment->SetStaticMesh(wallMesh);
		WallSegment->SetMaterial(0,material);
		WallSegment->SetWorldScale3D(FVector(0.5,1, 2.5));
		WallSegment->SetCastShadow(false);
		WallSegment->SetWorldRotation(rotation);
		WallSegments.Add(WallSegment);
	}
	bool leftCheck = false;
	int wallCount=1;

	WallSegments[0]->SetWorldLocation(mouseLocation);
		

	for (int x = 1; x < wallSegments; x++)
	{
		if (leftCheck)
		{
			WallSegments[x]->SetWorldLocation(WallSegments[0]->GetComponentLocation() + -1 * wallCount * WallSegments[0]->GetRightVector()*100);
			wallCount++;
		}
		else
		{
			WallSegments[x]->SetWorldLocation(WallSegments[0]->GetComponentLocation() + wallCount * WallSegments[0]->GetRightVector()*100);
		}
		leftCheck = !leftCheck;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Wall Should be built")));
}

void AWall::despawn()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Despawn")));
	this->Destroy();
}

