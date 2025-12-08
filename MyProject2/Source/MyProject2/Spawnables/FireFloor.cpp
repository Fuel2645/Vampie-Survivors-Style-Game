// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject2/Spawnables/FireFloor.h"

// Sets default values
AFireFloor::AFireFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_Spline = CreateDefaultSubobject <USplineComponent>(TEXT("Spline"));
	SetRootComponent(m_Spline);

	ConstructorHelpers::FObjectFinder<UStaticMesh> meshOBJ(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	floorMesh = meshOBJ.Object;

	ConstructorHelpers::FObjectFinder<UMaterialInterface> materialOBJ(TEXT("/Game/Material/MI_Fire_Gradiant.MI_Fire_Gradiant"));
	materialRef = materialOBJ.Object;

}

// Called when the game starts or when spawned
void AFireFloor::BeginPlay()
{
	Super::BeginPlay();
	actorToFollow = GetWorld()->GetFirstPlayerController()->GetPawn();
	FTimerHandle pathTimer;
	GetWorld()->GetTimerManager().SetTimer(pathTimer, this, &AFireFloor::pathLogic, 0.05f, true);


}

// Called every frame
void AFireFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFireFloor::pathLogic()
{
	UpdatePath();
	UpdateSplineMeshes();
}

void AFireFloor::UpdatePath()
{
	if (!actorToFollow)
		return;

	FVector currentLocation = actorToFollow->GetActorLocation();

	if (lastLocation.IsZero())
	{
		m_Spline->AddSplinePoint(currentLocation, ESplineCoordinateSpace::World);
		lastLocation = currentLocation;
		return;
	}

	float distance = FVector::Dist(currentLocation, lastLocation);

	if (distance >= minPointSpacing)
	{
		m_Spline->AddSplinePoint(currentLocation, ESplineCoordinateSpace::World);
		lastLocation = currentLocation;
	}

}

void AFireFloor::UpdateSplineMeshes()
{
	int32 numOfPoints = m_Spline->GetNumberOfSplinePoints();
	int32 neededMeshes = numOfPoints - 1;

	while (m_SplinePoints.Num() < neededMeshes)
	{
		USplineMeshComponent* newMesh = NewObject<USplineMeshComponent>(this);
		newMesh->RegisterComponent();
		newMesh->SetMobility(EComponentMobility::Movable);
		newMesh->SetWorldScale3D(FVector(1, 1, 0.2));
		newMesh->AttachToComponent(m_Spline, FAttachmentTransformRules::KeepRelativeTransform);
		newMesh->SetStaticMesh(floorMesh);
		newMesh->SetCastShadow(false);
		if (materialRef)
			newMesh->SetMaterial(0,materialRef);

		newMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		newMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
		newMesh->OnComponentBeginOverlap.AddDynamic(this, &AFireFloor::OnOverlapBegin);
		newMesh->OnComponentEndOverlap.AddDynamic(this, &AFireFloor::OnOverlapEnd);

		m_SplinePoints.Add(newMesh);
	}

	for (int32 x = 0; x < neededMeshes; x++)
	{
		FVector StartPos = m_Spline->GetLocationAtSplinePoint(x, ESplineCoordinateSpace::Local);
		FVector StartTangent = m_Spline->GetTangentAtSplinePoint(x, ESplineCoordinateSpace::Local);
		FVector EndPos = m_Spline->GetLocationAtSplinePoint(x + 1, ESplineCoordinateSpace::Local);
		FVector EndTangent = m_Spline->GetTangentAtSplinePoint(x + 1, ESplineCoordinateSpace::Local);

		m_SplinePoints[x]->SetStartAndEnd(StartPos, StartTangent, EndPos, EndTangent);
	}

}

void AFireFloor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IUnitInteraction* Interface = Cast<IUnitInteraction>(OtherActor))
	{
		Interface->FireDamageStart(m_Damage, 0.5);
	}
}

void AFireFloor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IUnitInteraction* Interface = Cast<IUnitInteraction>(OtherActor))
	{
		Interface->FireDamageEnd();
	}
}

