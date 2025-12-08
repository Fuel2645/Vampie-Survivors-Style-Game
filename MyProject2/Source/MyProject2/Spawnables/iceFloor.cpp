// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject2/Spawnables/iceFloor.h"

// Sets default values
AiceFloor::AiceFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	floorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	floorMesh->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshOBJ(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	UStaticMesh* Asset = MeshOBJ.Object;
	floorMesh->SetStaticMesh(Asset);
	ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("/Game/Material/MI_Ice_Gradiant.MI_Ice_Gradiant"));
	floorMesh->SetMaterial(0, Material.Object);
	floorMesh->SetCastShadow(false);
	floorMesh->SetRelativeScale3D(FVector(4, 4, 0.2));
	floorMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	floorMesh->OnComponentBeginOverlap.AddDynamic(this, &AiceFloor::OnOverlapBegin);
	floorMesh->OnComponentEndOverlap.AddDynamic(this, &AiceFloor::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AiceFloor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AiceFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AiceFloor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IPlayerInteractionInterface* Interface = Cast<IPlayerInteractionInterface>(OtherActor))
	{
		Interface->IceSurfaceStart(m_Friction, m_Braking);
	}
}

void AiceFloor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IPlayerInteractionInterface* Interface = Cast<IPlayerInteractionInterface>(OtherActor))
	{
		Interface->IceSurfaceEnd();
	}
}

