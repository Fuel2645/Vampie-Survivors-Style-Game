// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawnables/PoisonPool.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
APoisonPool::APoisonPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	baseMesh->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshOBJ(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	UStaticMesh* Asset = MeshOBJ.Object;
	baseMesh->SetStaticMesh(Asset);
	baseMesh->SetCastShadow(false);
	baseMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	baseMesh->SetGenerateOverlapEvents(true);
	baseMesh->OnComponentBeginOverlap.AddDynamic(this, &APoisonPool::OnOverlapBegin);
	baseMesh->OnComponentEndOverlap.AddDynamic(this, &APoisonPool::OnOverlapEnd);
	baseMesh->SetRelativeScale3D(FVector(3, 3, 0.01));

	ConstructorHelpers::FObjectFinder<UMaterialInterface> MeshMaterial(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Material/MI_DarkGreen.MI_DarkGreen'"));
	if (MeshMaterial.Succeeded())
	{
		UMaterialInterface* LoadedMat = MeshMaterial.Object;
		baseMesh->SetMaterial(0, LoadedMat);
	}


}

// Called when the game starts or when spawned
void APoisonPool::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer
	(
		lifespawnTimer,
		this,
		&APoisonPool::despawn,
		5.0f,
		true
	);


	
}

// Called every frame
void APoisonPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APoisonPool::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IUnitInteraction* Interface = Cast<IUnitInteraction>(OtherActor))
	{
		if (!overlappingActors.Contains(OtherActor))
		{
			Interface->PoisonDamageStart(m_Damage, 1.0f);
			overlappingActors.Add(OtherActor);
		}
		
	}
	
}

void APoisonPool::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IUnitInteraction* Interface = Cast<IUnitInteraction>(OtherActor))
	{
		if (overlappingActors.Contains(OtherActor))
		{
			Interface->PoisonDamageEnd();
			overlappingActors.Remove(OtherActor);
		}
		
	}
}

void APoisonPool::despawn()
{
	this->Destroy();
}


