// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EarthConstruct.h"

// Sets default values
AEarthConstruct::AEarthConstruct()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AEarthConstruct_Controller::StaticClass();


	m_Controller = Cast<AAIController>(GetController());

	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshOBJ(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	UStaticMesh* Asset = MeshOBJ.Object;
	Cube->SetStaticMesh(Asset);
	Cube->SetRelativeScale3D(FVector(0.25, 0.25, 1.0));
	Cube->SetupAttachment(RootComponent);
	Cube->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Cube->SetGenerateOverlapEvents(true);
	Cube->SetCastShadow(false);

	ConstructorHelpers::FObjectFinder<UMaterialInterface> CubeMaterial(TEXT("/Game/Material/MI_Ground_Gradiant.MI_Ground_Gradiant"));
	if (CubeMaterial.Succeeded())
	{
		UMaterialInterface* LoadedMat = CubeMaterial.Object;
		Cube->SetMaterial(0, LoadedMat);
	}

	Gun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> GunOBJ(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	UStaticMesh* GunAsset = MeshOBJ.Object;
	Gun->SetStaticMesh(GunAsset);
	Gun->SetRelativeScale3D(FVector(1.0, 0.5, 0.2));
	Gun->SetRelativeLocation(FVector(100, 0, 10));
	Gun->SetupAttachment(Cube);
	Gun->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Gun->SetGenerateOverlapEvents(true);
	Gun->SetCastShadow(false);


	ConstructorHelpers::FObjectFinder<UMaterialInterface> GunMaterial(TEXT("/Game/Material/MI_Ground_Gradiant.MI_Ground_Gradiant"));
	if (GunMaterial.Succeeded())
	{
		UMaterialInterface* LoadedMat = GunMaterial.Object;
		Gun->SetMaterial(0, LoadedMat);
	}

	GetCharacterMovement()->MaxWalkSpeed = 500.f;

	GetCharacterMovement()->bOrientRotationToMovement = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = true;
	Cube->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);
	Cube->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Overlap);
}

// Called when the game starts or when spawned
void AEarthConstruct::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(0.7, 0.7, 0.7));
}

// Called every frame
void AEarthConstruct::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEarthConstruct::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

