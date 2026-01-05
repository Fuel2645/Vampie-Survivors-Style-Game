// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/XPShard.h"

// Sets default values
AXPShard::AXPShard()
{
	PrimaryActorTick.bCanEverTick = false;

	shardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = shardMesh;
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshOBJ(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	UStaticMesh* Asset = MeshOBJ.Object;
	shardMesh->SetStaticMesh(Asset);
	shardMesh->SetCastShadow(false);
	shardMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	shardMesh->SetRelativeScale3D(FVector(0.2, 0.2, 0.7));
	shardMesh->OnComponentBeginOverlap.AddDynamic(this, &AXPShard::OnOverlapBegin);

}

void AXPShard::move()
{
	FVector Direction = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - this->GetActorLocation();
	this->SetActorRotation(FMath::RInterpTo(this->GetActorRotation(), Direction.Rotation(), GetWorld()->GetDeltaSeconds(), 90.f));

	this->SetActorLocation(this->GetActorLocation() + this->GetActorForwardVector() * m_MoveSpeed);
	m_MoveSpeed += 0.1f;

}


// Called when the game starts or when spawned
void AXPShard::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("ShardValue: %i"), XPGainAmount));
}

void AXPShard::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	switch (m_ShardType)
	{
	case ShardTypes::Red:
	{                                                                                                                                                                                                                                        
		UMaterialInterface* LoadedMat = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Material/MI_Red.MI_Red'")));
		shardMesh->SetMaterial(0, LoadedMat);
		XPGainAmount = 50;
		break;
	}
	case ShardTypes::Green:
	{
		UMaterialInterface* LoadedMat = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Material/MI_Green.MI_Green'")));
		shardMesh->SetMaterial(0, LoadedMat);
		XPGainAmount = 40;
		break;
	}
	case ShardTypes::Blue:
	{
		UMaterialInterface* LoadedMat = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Material/MI_Blue.MI_Blue'")));
		shardMesh->SetMaterial(0, LoadedMat);
		XPGainAmount = 25;

		break;
	}
	case ShardTypes::Purple:
	{
		UMaterialInterface* LoadedMat = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Material/MI_Purple.MI_Purple'")));
		shardMesh->SetMaterial(0, LoadedMat);
		XPGainAmount = 500;

		break;
	}
	default:
		break;
	}

}




// Called every frame
void AXPShard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AXPShard::XPShardMove()
{
	FTimerHandle moveTimer;

	GetWorld()->GetTimerManager().SetTimer
	(
		moveTimer,
		this,
		&AXPShard::move,
		0.01f,
		true
	);


}

void AXPShard::Initalise(ShardTypes givenType)
{
	m_ShardType = givenType;

	switch (m_ShardType)
	{
	case ShardTypes::Red:
	{
		UMaterialInterface* LoadedMat = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Material/MI_Red.MI_Red'")));
		shardMesh->SetMaterial(0, LoadedMat);
		XPGainAmount = 50;
		break;
	}
	case ShardTypes::Green:
	{
		UMaterialInterface* LoadedMat = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Material/MI_Green.MI_Green'")));
		shardMesh->SetMaterial(0, LoadedMat);
		XPGainAmount = 40;
		break;
	}
	case ShardTypes::Blue:
	{
		UMaterialInterface* LoadedMat = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Material/MI_Blue.MI_Blue'")));
		shardMesh->SetMaterial(0, LoadedMat);
		XPGainAmount = 25;

		break;
	}
	case ShardTypes::Purple:
	{
		UMaterialInterface* LoadedMat = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Material/MI_Purple.MI_Purple'")));
		shardMesh->SetMaterial(0, LoadedMat);
		XPGainAmount = 500;


		break;
	}
	default:
		UMaterialInterface* LoadedMat = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("'/Game/Material/MI_Error.MI_Error'")));
		shardMesh->SetMaterial(0, LoadedMat);
		XPGainAmount = 0;
		break;
	}

}

void AXPShard::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetWorld()->GetFirstPlayerController()->GetPawn() && OtherComp->IsA(UCapsuleComponent::StaticClass()) )
	{
		if (IXP_Interface* Interface = Cast<IXP_Interface>(GetWorld()->GetFirstPlayerController()))
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("ShardValue: %i"), XPGainAmount));
			Interface->XPChange(XPGainAmount);
			this->Destroy();
		}
	}


}

