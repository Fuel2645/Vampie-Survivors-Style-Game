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


	ConstructorHelpers::FObjectFinder<UMaterialInterface> GunMaterial(TEXT("/Game/Material/MI_Orange.MI_Orange"));
	if (GunMaterial.Succeeded())
	{
		UMaterialInterface* LoadedMat = GunMaterial.Object;
		Gun->SetMaterial(0, LoadedMat);
	}

	BaseCircle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BasePlate"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> BasePlateOBJ(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	UStaticMesh* PlateAsset = BasePlateOBJ.Object;
	BaseCircle->SetStaticMesh(PlateAsset);
	BaseCircle->SetRelativeScale3D(FVector(0.4, 0.4, 0.01));
	BaseCircle->SetRelativeLocation(FVector(0, 0, -88));
	BaseCircle->SetupAttachment(RootComponent);
	BaseCircle->SetCollisionProfileName(TEXT("NoCollision"));
	BaseCircle->SetGenerateOverlapEvents(false);
	BaseCircle->SetCastShadow(false);

	ConstructorHelpers::FObjectFinder<UMaterialInterface> BasePlateMaterial(TEXT("/Game/Material/MI_Black.MI_Black"));
	if (BasePlateMaterial.Succeeded())
	{
		UMaterialInterface* LoadedMat = BasePlateMaterial.Object;
		BaseCircle->SetMaterial(0, LoadedMat);
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
	this->GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemy_Base::OnOverlapBegin);
	this->GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AEnemy_Base::OnOverlapEnd);

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_NavWalking);



	healthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Bar"));
	healthBar->SetupAttachment(RootComponent);
	healthBar->SetWidgetSpace(EWidgetSpace::World);
	healthBar->SetDrawSize(FVector2D(100.f, 10.f));
	healthBar->SetRelativeLocation(FVector(0, -20, 100));
	healthBar->SetRelativeRotation(FRotator(90, 0,  0));
	healthBar->SetUsingAbsoluteRotation(true);

	ConstructorHelpers::FClassFinder<UUserWidget> healthBarBP(TEXT("/Game/UI/WBP_EnemyHealthBar"));

	if (healthBarBP.Class)
	{
		healthBarWidgetClass = healthBarBP.Class;
	}

	
}

// Called when the game starts or when spawned
void AEnemy_Base::BeginPlay()
{
	Super::BeginPlay();

	isActive = true;

	if (healthBarWidgetClass)
	{

		healthBar->SetWidgetClass(healthBarWidgetClass);
	}
}

// Called every frame

void AEnemy_Base::Damage(float inDamage)
{
	m_HP -= inDamage;

	if (UHealthBar* HB = Cast<UHealthBar>(healthBar->GetUserWidgetObject()))
	{
		HB->SetBarPercent(m_HP / m_MaxHp);
	}


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

	if (UHealthBar* HB = Cast<UHealthBar>(healthBar->GetUserWidgetObject()))
	{
		HB->SetBarPercent(m_HP/m_MaxHp);
	}


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

	m_MaxHp = data->HP;
	m_HP = data->HP;
	m_Damage = data->Damage;
	
	SetActorScale3D(data->size);
	GetCharacterMovement()->MaxWalkSpeed = data->Speed;
	baseMovementSpeed = data->Speed;
	m_Shardtype = data->ShardType;
	
	if (UHealthBar* HB = Cast<UHealthBar>(healthBar->GetUserWidgetObject()))
	{
		HB->SetBarPercent(1);
	}

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

void AEnemy_Base::PlayerDamage()
{
	if (IPlayerInteractionInterface* interface = Cast<IPlayerInteractionInterface>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{

		interface->Damage(m_Damage);
	}
}

void AEnemy_Base::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName("Player")) && !GetWorld()->GetTimerManager().IsTimerActive(damageTimer) && OtherComp->IsA(UCapsuleComponent::StaticClass()))
	{
		PlayerDamage();
		GetWorld()->GetTimerManager().SetTimer(damageTimer, this, &AEnemy_Base::PlayerDamage, 1.5f, true);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Overlap Start")));
	}
}

void AEnemy_Base::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag(FName("Player")) && GetWorld()->GetTimerManager().IsTimerActive(damageTimer) && OtherComp->IsA(UCapsuleComponent::StaticClass()))
	{
		GetWorld()->GetTimerManager().ClearTimer(damageTimer);
		damageTimer.Invalidate();
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Overlap End")));
	}
}



