// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawnables/BrokenGround.h"

// Sets default values
ABrokenGround::ABrokenGround()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	circleBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("circleBase"));
	
	circleBase->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshOBJ(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	UStaticMesh* Asset = MeshOBJ.Object;
	circleBase->SetStaticMesh(Asset);
	ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("/Game/Material/MI_Ground_Gradiant.MI_Ground_Gradiant"));
	circleBase->SetMaterial(0, Material.Object);
	circleBase->SetCastShadow(false);
	circleBase->SetRelativeScale3D(FVector(4, 4, 0.2));

	cylinderCollision = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cylinderCollision"));
	cylinderCollision->SetupAttachment(circleBase);
	cylinderCollision->SetStaticMesh(Asset);
	cylinderCollision->SetCastShadow(false);
	cylinderCollision->SetHiddenInGame(true);
	cylinderCollision->SetRelativeScale3D(FVector(1, 1, 1.5/0.2));
	cylinderCollision->OnComponentBeginOverlap.AddDynamic(this, &ABrokenGround::OnOverlapBegin);
	cylinderCollision->SetRelativeLocation(circleBase->GetRelativeLocation() + circleBase->GetUpVector()*50.f * (1.5/0.2));



	ConstructorHelpers::FObjectFinder<UMaterialInterface> spikeMaterial(TEXT("/Game/Material/MI_Ice_Gradiant.MI_Ice_Gradiant"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> spikeMesh(TEXT("/Engine/BasicShapes/Cone.Cone"));
	Asset = spikeMesh.Object;

	for(int x = 0; x < 4; x++) //Initalising
	{
		FName spikeName(*FString::Printf(TEXT("Spike_Center_%d"), x));

		UStaticMeshComponent* spike = CreateDefaultSubobject<UStaticMeshComponent>(spikeName);
		float randHeight = FMath::FRandRange(0.8, 1.6);
		 
		spike->SetRelativeScale3D(FVector(0.8, 0.8, randHeight) / circleBase->GetRelativeScale3D());
		spike->SetupAttachment(circleBase);
		spike->SetStaticMesh(Asset);
		spike->SetMaterial(0, spikeMaterial.Object);
		spike->SetCollisionProfileName(TEXT("NoCollision"));
		spike->SetCastShadow(false);
		spikeMeshes.Add(spike);
	}
	for (int x = 0; x < 8; x++)
	{
		FName spikeName(*FString::Printf(TEXT("Spike_%d"), x));

		UStaticMeshComponent* spike = CreateDefaultSubobject<UStaticMeshComponent>(spikeName);
		float randHeight = FMath::FRandRange(0.6, 1.2);

		spike->SetRelativeScale3D(FVector(0.6, 0.6, randHeight) / circleBase->GetRelativeScale3D());
		spike->SetupAttachment(circleBase);
		spike->SetStaticMesh(Asset);
		spike->SetMaterial(0, spikeMaterial.Object);
		spike->SetCollisionProfileName(TEXT("NoCollision"));
		
		spike->SetCastShadow(false);
		spikeMeshes.Add(spike);
	}

	//Even Spacing positions

	double Angle = (360 / 4) * (PI / 180);

	TArray<FVector> Temp;
	TArray<FVector> newTemp;

	if (!Temp.IsEmpty())
		Temp.Empty();

	Temp.Init(FVector(0, 0, 0), 4);

	Temp[0] = circleBase->GetRelativeLocation() + circleBase->GetForwardVector() * 20.f;
	spikeMeshes[0]->SetRelativeLocation(Temp[0]);

	for (int x = 1; x < 4; x++)
	{
		Temp[x] = FVector(Temp[x - 1].X * cos(Angle) - Temp[x - 1].Y * sin(Angle), (Temp[x - 1].X * sin(Angle) + Temp[x - 1].Y * cos(Angle)),0);
		spikeMeshes[x]->SetRelativeLocation(Temp[x]);
	}

	if (!newTemp.IsEmpty())
		newTemp.Empty();


	newTemp.Init(FVector(0, 0, 0), 8);

	double newAngle = (360 / 8) * (PI / 180);

	newTemp[0] = circleBase->GetRelativeLocation() + circleBase->GetForwardVector() * 40.0f;
	spikeMeshes[4]->SetRelativeLocation(newTemp[0]);

	for (int x = 1; x < 8; x++)
	{
		newTemp[x] = FVector(newTemp[x - 1].X * cos(newAngle) - newTemp[x - 1].Y * sin(newAngle), (newTemp[x - 1].X * sin(newAngle) + newTemp[x - 1].Y * cos(newAngle)),0);
		spikeMeshes[x+4]->SetRelativeLocation(newTemp[x]);
	}

	for (int x = 0; x < spikeMeshes.Num(); x++)
	{
		spikeMeshes[x]->SetRelativeLocation(spikeMeshes[x]->GetRelativeLocation() + FVector(0, 0, 1) * 50.f * spikeMeshes[x]->GetRelativeScale3D().Z);
	}
}

// Called when the game starts or when spawned
void ABrokenGround::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(movementTimer, this, &ABrokenGround::Movement, 0.01f, true);
}

// Called every frame
void ABrokenGround::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABrokenGround::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IUnitInteraction* interface = Cast<IUnitInteraction>(OtherActor))
	{
		interface->Damage(30.0f);
		interface->StunStart(1.5f);
	}
}

void ABrokenGround::Movement()
{
	if (movementCounter == 20)
	{
		GetWorld()->GetTimerManager().ClearTimer(movementTimer);
		cylinderCollision->DestroyComponent();
	}
	else
	{
		this->SetActorLocation(GetActorLocation() + FVector(0, 0, 5));
		movementCounter++;
	}
}

