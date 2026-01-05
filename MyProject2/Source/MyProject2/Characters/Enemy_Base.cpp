// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemy_Base.h"

// Sets default values
AEnemy_Base::AEnemy_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AEnemyController::StaticClass();


	m_Controller = Cast<AAIController>(GetController());

	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshOBJ(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	UStaticMesh* Asset = MeshOBJ.Object;
	Cube->SetStaticMesh(Asset);
	Cube->SetRelativeScale3D(FVector(0.25, 0.25, 1.0));
	Cube->SetupAttachment(RootComponent);
	Cube->SetCollisionProfileName(TEXT("NoCollision"));
	Cube->SetGenerateOverlapEvents(true);
	Cube->SetCastShadow(false);

	ConstructorHelpers::FObjectFinder<UMaterialInterface> CubeMaterial(TEXT("/Game/Material/MI_Red.MI_Red"));
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
	Gun->SetCollisionProfileName(TEXT("NoCollision"));
	Gun->SetGenerateOverlapEvents(false);
	Gun->SetCastShadow(false);


	ConstructorHelpers::FObjectFinder<UMaterialInterface> GunMaterial(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Material/MI_Orange.MI_Orange'"));
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

	this->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Block);
	this->GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	this->GetCapsuleComponent()->SetCapsuleRadius(20.f);

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_NavWalking);
}

// Called when the game starts or when spawned
void AEnemy_Base::BeginPlay()
{
	Super::BeginPlay();

	isActive = true;


}

// Called every frame

void AEnemy_Base::Damage(float inDamage)
{
	m_HP -= inDamage;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Damage");
	DeathCheck();
}

void AEnemy_Base::PoisonDamageStart(float inDamage, float TimeBetween)
{
	if (!isPoisoned)
	{
		Damage(inDamage);
		isPoisoned = true;
		poisonDamage = inDamage;
		GetWorld()->GetTimerManager().SetTimer
		(
			poisonTimer,
			this,
			&AEnemy_Base::PoisonDamage,
			TimeBetween,
			true
		);


	}	




}

void AEnemy_Base::PoisonDamage()
{
	m_HP -= poisonDamage;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Damage");
	DeathCheck();
}

void AEnemy_Base::PoisonDamageEnd()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(poisonTimer))
	{
		GetWorld()->GetTimerManager().ClearTimer(poisonTimer);
		poisonTimer.Invalidate();
	}
		
}

void AEnemy_Base::SlowStart(float Duration, float slowPercentage)
{
	GetCharacterMovement()->MaxWalkSpeed = baseMovementSpeed * slowPercentage;
	FTimerHandle slowTimer;

	GetWorld()->GetTimerManager().SetTimer
	(
		slowTimer,
		this,
		&AEnemy_Base::SlowEnd,
		Duration,
		false
	);
}

void AEnemy_Base::SlowEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = baseMovementSpeed;
}

void AEnemy_Base::StunStart(float Duration)
{
}

void AEnemy_Base::StunEnd()
{
}

void AEnemy_Base::Initalise(FST_EnemyDataRow* data)
{
	Cube->SetMaterial(0, data->Colour);

	m_HP = data->HP;
	
	SetActorScale3D(data->size);
	GetCharacterMovement()->MaxWalkSpeed = data->Speed;
	baseMovementSpeed = data->Speed;
	m_Shardtype = data->ShardType;
}

void AEnemy_Base::DeathCheck()
{
	if (m_HP <= 0 && isActive)
	{
		isActive = false;
		FActorSpawnParameters spawnParams;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		spawnParams.Owner = this;
		spawnParams.Instigator = GetInstigator();

		AXPShard* deathShard = GetWorld()->SpawnActor<AXPShard>(AXPShard::StaticClass(), Cube->GetComponentLocation(), Cube->GetComponentRotation(), spawnParams);

			switch (m_Shardtype)
			{
			case ShardTypes::Red:
				deathShard->Initalise(ShardTypes::Red);
				break;
			case ShardTypes::Blue:
				deathShard->Initalise(ShardTypes::Blue);
				break;
			case ShardTypes::Purple:
				deathShard->Initalise(ShardTypes::Purple);
				break;
			case ShardTypes::Green:
				deathShard->Initalise(ShardTypes::Green);
				break;
			default:
				break;
			}
			this->Destroy();
	}

}



