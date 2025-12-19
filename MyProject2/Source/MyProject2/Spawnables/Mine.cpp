// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawnables/Mine.h"

// Sets default values
AMine::AMine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	baseMesh->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshOBJ(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	UStaticMesh* Asset = MeshOBJ.Object;
	baseMesh->SetStaticMesh(Asset);
	baseMesh->SetCastShadow(false);
	baseMesh->SetRelativeScale3D(FVector(0.6, 0.6, 0.2));

	ConstructorHelpers::FObjectFinder<UMaterialInterface> MeshMaterial(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Material/MI_Black.MI_Black'"));
	if (MeshMaterial.Succeeded())
	{
		UMaterialInterface* LoadedMat = MeshMaterial.Object;
		baseMesh->SetMaterial(0, LoadedMat);
	}
}

// Called when the game starts or when spawned
void AMine::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer
	(
		ExplosionTimer,
		this,
		&AMine::Explosion,
		TimeTillExplosion,
		false
	);
	
}

// Called every frame
void AMine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMine::Explosion()
{
	USphereComponent* explosionSphere = NewObject<USphereComponent>(this);
	if (explosionSphere)
	{
		explosionSphere->SetSphereRadius(250.0f);
		explosionSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		explosionSphere->RegisterComponent();
		explosionSphere->SetCollisionResponseToAllChannels(ECR_Overlap);
		explosionSphere->SetRelativeLocation(RootComponent->GetRelativeLocation());
		explosionSphere->OnComponentBeginOverlap.AddDynamic(this, &AMine::OnOverlapBegin);
	}
	ExplosionTimer.Invalidate();
	GetWorld()->GetTimerManager().SetTimer
	(
		ExplosionTimer,
		this,
		&AMine::EndMine,
		0.2f,
		false
	);

}

void AMine::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IUnitInteraction* Interface = Cast<IUnitInteraction>(OtherActor))
	{
		Interface->Damage(15.f);
	}

}

void AMine::EndMine()
{
	this->Destroy();
}

