// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject2/Spawnables/IceBeam.h"

// Sets default values
AIceBeam::AIceBeam()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_Beam = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	m_Beam->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshOBJ(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	UStaticMesh* Asset = MeshOBJ.Object;
	m_Beam->SetStaticMesh(Asset);
	ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("/Game/Material/MI_Ice_Gradiant.MI_Ice_Gradiant"));
	m_Beam->SetMaterial(0,Material.Object);
	m_Beam->SetCastShadow(false);
	m_Beam->SetRelativeScale3D(FVector(0.5, 0.5, 40));
	m_Beam->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	m_Beam->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);
	m_Beam->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Overlap);
	m_Beam->OnComponentBeginOverlap.AddDynamic(this, &AIceBeam::OnOverlapBegin);
	m_Beam->SetRelativeRotation(FRotator(0, 90, 90));
	m_Beam->SetRelativeLocation(FVector(1600, 0, 0));
}

// Called when the game starts or when spawned
void AIceBeam::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AIceBeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIceBeam::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IUnitInteraction* Interface = Cast<IUnitInteraction>(OtherActor))
	{
		Interface->SlowStart(5.0, 0.5);
		Interface->Damage(5.0f);
	}
}

