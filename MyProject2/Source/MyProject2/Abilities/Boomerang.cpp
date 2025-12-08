// Fill out your copyright notice in the Description page of Project Settings.


#include "Boomerang.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ABoomerang::ABoomerang()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	baseMesh->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshOBJ(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	UStaticMesh* Asset = MeshOBJ.Object;
	baseMesh->SetStaticMesh(Asset);
	baseMesh->SetCastShadow(false);
	baseMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	baseMesh->SetGenerateOverlapEvents(true);
	baseMesh->SetRelativeScale3D(FVector(1, 1, 0.1));
	baseMesh->OnComponentBeginOverlap.AddDynamic(this, &ABoomerang::OnOverlapBegin);
	baseMesh->OnComponentEndOverlap.AddDynamic(this, &ABoomerang::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ABoomerang::BeginPlay()
{
	Super::BeginPlay();
	

	for (UActorComponent* comp : GetWorld()->GetFirstPlayerController()->GetPawn()->GetComponents())
	{
		if (comp->GetFName() == FName("Gun"))
		{
			gunComponent = Cast<USceneComponent>(comp);
		}
	}




	GetWorld()->GetTimerManager().SetTimer
	(
		movementTimer,
		this,
		&ABoomerang::Movement,
		0.01f,
		true
	);

}

// Called every frame
void ABoomerang::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoomerang::Movement()
{
	if(MovementCount <= 30)
	{
		this->SetActorRotation(FMath::RInterpTo(this->GetActorRotation(), this->GetActorRotation() + FRotator(0, 35,0), GetWorld()->GetDeltaSeconds(), 10.0f));
	}
	else if (MovementCount > 30 && MovementCount <= 40)
	{
		this->SetActorRotation(FMath::RInterpTo(this->GetActorRotation(), this->GetActorRotation() + FRotator(0, 0, 18), GetWorld()->GetDeltaSeconds(), 10.0f));
	}
	else if (MovementCount > 40)
	{
		FVector Direction = (gunComponent->GetComponentLocation() - this->GetActorLocation());

		this->SetActorRotation(FMath::RInterpTo(this->GetActorRotation(), Direction.Rotation(), GetWorld()->GetDeltaSeconds(), 10.0f));
	}

	this->SetActorLocation(this->GetActorLocation() + this->GetRootComponent()->GetForwardVector() * 10.f);
	MovementCount++;
}

void ABoomerang::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetWorld()->GetFirstPlayerController()->GetPawn() && MovementCount > 40)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Destory");
		this->Destroy();
	}
	else if (IUnitInteraction* Interface = Cast<IUnitInteraction>(OtherActor))
	{
		if (!overlappingActors.Contains(OtherActor))
		{
			Interface->Damage(m_Damage);
			overlappingActors.Add(OtherActor);
		}
	}

}

void ABoomerang::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (overlappingActors.Contains(OtherActor))
		overlappingActors.Remove(OtherActor);

}





