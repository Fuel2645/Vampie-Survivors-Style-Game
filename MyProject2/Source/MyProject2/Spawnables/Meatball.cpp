// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawnables/Meatball.h"

// Sets default values
AMeatball::AMeatball()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeatballMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeatballMesh->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshOBJ(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	UStaticMesh* Asset = MeshOBJ.Object;
	MeatballMesh->SetStaticMesh(Asset);
	MeatballMesh->SetCastShadow(false);
	MeatballMesh->SetCollisionProfileName(TEXT("Custom"));
	MeatballMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeatballMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeatballMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	MeatballMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);
	MeatballMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECR_Overlap);
	MeatballMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Overlap);
	MeatballMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	MeatballMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	MeatballMesh->SetGenerateOverlapEvents(true);
	MeatballMesh->SetRelativeScale3D(FVector(0.4, 0.4, 0.4));
	MeatballMesh->OnComponentBeginOverlap.AddDynamic(this, &AMeatball::OnOverlapBegin);
	MeatballMesh->OnComponentEndOverlap.AddDynamic(this, &AMeatball::OnOverlapEnd);
	ConstructorHelpers::FObjectFinder<UMaterialInterface> MeshMaterial(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Material/MI_Brown.MI_Brown'"));
	MeatballMesh->SetMaterial(0, MeshMaterial.Object);


	m_MoveSpeed = 5.0f;

}

// Called when the game starts or when spawned
void AMeatball::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle movementTimer;

	GetWorld()->GetTimerManager().SetTimer
	(
		movementTimer,
		this,
		&AMeatball::Movement,
		0.01f,
		true
	);


}

// Called every frame
void AMeatball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMeatball::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	USphereComponent* explosionSphere = NewObject<USphereComponent>(this);
	if (explosionSphere)
	{
		explosionSphere->RegisterComponent();
		explosionSphere->SetSphereRadius(250.0f);
		explosionSphere->SetGenerateOverlapEvents(true);
		explosionSphere->SetRelativeLocation(RootComponent->GetRelativeLocation());
		explosionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
		explosionSphere->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
		explosionSphere->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);
		explosionSphere->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECR_Overlap);
		explosionSphere->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Overlap);
		explosionSphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
		explosionSphere->OnComponentBeginOverlap.AddDynamic(this, &AMeatball::ExplosionOverlapBegin);
	}
	if (IUnitInteraction* Interface = Cast<IUnitInteraction>(OtherActor))
	{
		Interface->Damage(20.f);
	}

	FTimerHandle deathTimer;
	GetWorld()->GetTimerManager().SetTimer(deathTimer, this, &AMeatball::LookAtTheFlowers, 0.2f, false);
}

void AMeatball::ExplosionOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IUnitInteraction* Interface = Cast<IUnitInteraction>(OtherActor))
	{
		Interface->Damage(15.f);
	}
}

void AMeatball::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AMeatball::Movement()
{
	this->SetActorLocation(this->GetActorLocation() + this->GetActorUpVector() * -m_MoveSpeed);
}

