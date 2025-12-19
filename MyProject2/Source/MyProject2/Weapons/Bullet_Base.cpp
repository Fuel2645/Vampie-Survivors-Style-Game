// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Bullet_Base.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABullet_Base::ABullet_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	bulletMesh->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshOBJ(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	UStaticMesh* Asset = MeshOBJ.Object;
	bulletMesh->SetStaticMesh(Asset);
	bulletMesh->SetCastShadow(false);
	bulletMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	bulletMesh->SetGenerateOverlapEvents(true);
	bulletMesh->SetRelativeScale3D(FVector(0.2, 0.2, 0.2));
	bulletMesh->OnComponentBeginOverlap.AddDynamic(this, &ABullet_Base::OnOverlapBegin);
	bulletMesh->OnComponentEndOverlap.AddDynamic(this, &ABullet_Base::OnOverlapEnd);

	ConstructorHelpers::FObjectFinder<UMaterialInterface> MeshMaterial(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Material/MI_Orange.MI_Orange'"));
	if (MeshMaterial.Succeeded())
	{
		UMaterialInterface* LoadedMat = MeshMaterial.Object;
		bulletMesh->SetMaterial(0, LoadedMat);
	}

}

// Called when the game starts or when spawned
void ABullet_Base::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer
	(
		m_MovementTimer,
		this,
		&ABullet_Base::Movement,
		0.01f,
		true
	);
	
}

// Called every frame
void ABullet_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet_Base::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (IUnitInteraction* Interface = Cast<IUnitInteraction>(OtherActor))
	{
		if (!overlappingActors.Contains(OtherActor))
		{
			Interface->Damage(m_Damage);
			overlappingActors.Add(OtherActor);
		}
			
	}


}

void ABullet_Base::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (overlappingActors.Contains(OtherActor))
		overlappingActors.Remove(OtherActor);

}


void ABullet_Base::Movement()
{
	this->SetActorLocation(this->GetActorLocation() + this->GetActorForwardVector() * m_MovementSpeed);
}

