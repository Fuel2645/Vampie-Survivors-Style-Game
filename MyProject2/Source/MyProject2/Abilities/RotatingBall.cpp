// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/RotatingBall.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ARotatingBall::ARotatingBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	baseMesh->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshOBJ(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	UStaticMesh* Asset = MeshOBJ.Object;
	baseMesh->SetStaticMesh(Asset);
	baseMesh->SetCastShadow(false);
	baseMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	baseMesh->SetGenerateOverlapEvents(true);
	baseMesh->OnComponentBeginOverlap.AddDynamic(this, &ARotatingBall::OnOverlapBegin);
	baseMesh->OnComponentEndOverlap.AddDynamic(this, &ARotatingBall::OnOverlapEnd);


	ConstructorHelpers::FObjectFinder<UMaterialInterface> MeshMaterial(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Material/MI_Orange.MI_Orange'"));
	if (MeshMaterial.Succeeded())
	{
		UMaterialInterface* LoadedMat = MeshMaterial.Object;
		baseMesh->SetMaterial(0, LoadedMat);
	}


 }

// Called when the game starts or when spawned
void ARotatingBall::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		RotationTimer,
		this,
		&ARotatingBall::Rotation,
		0.01f,
		true
	);

}

// Called every frame
void ARotatingBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARotatingBall::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

void ARotatingBall::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (overlappingActors.Contains(OtherActor))
		overlappingActors.Remove(OtherActor);

}

void ARotatingBall::Rotation()
{
	FVector NextLocation(0,0,0);
	if (IsValid(this))
	{
		NextLocation = GetRootComponent()->GetRelativeLocation().RotateAngleAxis(2.f, FVector(0, 0, 1));
		SetActorRelativeLocation(NextLocation);
	}
}



