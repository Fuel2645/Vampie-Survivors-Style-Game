// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject2/Spawnables/IceShard.h"

// Sets default values
AIceShard::AIceShard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	shardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = shardMesh;
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshOBJ(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	UStaticMesh* Asset = MeshOBJ.Object;
	shardMesh->SetStaticMesh(Asset);
	ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("/Game/Material/MI_Ice_Gradiant.MI_Ice_Gradiant"));
	shardMesh->SetMaterial(0, Material.Object);
	shardMesh->SetCastShadow(false);
	shardMesh->SetRelativeScale3D(FVector(0,0,0));
	shardMesh->SetMobility(EComponentMobility::Movable);
	shardMesh->SetRelativeLocation(FVector(1600, 0, 0));
	shardMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	shardMesh->SetGenerateOverlapEvents(false);
	shardMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);
	shardMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Overlap);
	shardMesh->OnComponentBeginOverlap.AddDynamic(this, &AIceShard::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AIceShard::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer
	(
		generationTimer,
		this,
		&AIceShard::Enlarge,
		0.01,
		true
	);

	FTimerHandle movementTimer;
	GetWorld()->GetTimerManager().SetTimer
	(
		movementTimer,
		this,
		&AIceShard::ImReady,
		1.2,
		false
	);
	
}

// Called every frame
void AIceShard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIceShard::Enlarge()
{
	shardMesh->SetRelativeScale3D(shardMesh->GetRelativeScale3D() + FVector(0.03, 0.01, 0.01));
}

void AIceShard::ImReady()
{
	FTimerHandle movementTimer;
	GetWorld()->GetTimerManager().SetTimer
	(
		movementTimer,
		this,
		&AIceShard::Movement,
		0.01,
		true
	);
	this->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	shardMesh->SetGenerateOverlapEvents(true);
	GetWorld()->GetTimerManager().ClearTimer(generationTimer);
}

void AIceShard::Movement()
{
	this->SetActorLocation(this->GetActorLocation() + this->GetActorForwardVector() * m_MovementSpeed);
}

void AIceShard::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Overlap")));
	if (IUnitInteraction* Interface = Cast<IUnitInteraction>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Sucessful")));
		Interface->Damage(m_Damage);
	}

}

