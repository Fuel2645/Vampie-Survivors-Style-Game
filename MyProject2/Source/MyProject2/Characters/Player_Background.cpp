// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player_Background.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "Weapons/Bullet_Split.h"
#include "Kismet/KismetMathLibrary.h"





// Sets default values
APlayer_Background::APlayer_Background()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ConstructorHelpers::FObjectFinder<UInputMappingContext> MC(TEXT("/Game/Input/IMC_PLayer.IMC_PLayer"));
	inputMappingContext = MC.Object;

	ConstructorHelpers::FObjectFinder<UInputAction> IA_Move(TEXT("/Game/Input/IA_Movement.IA_Movement"));
	inputMove = IA_Move.Object;

	ConstructorHelpers::FObjectFinder<UInputAction> IA_Shoot(TEXT("/Game/Input/IA_Shoot.IA_Shoot"));
	inputShoot = IA_Shoot.Object;

	ConstructorHelpers::FObjectFinder<UInputAction> IA_Dash(TEXT("/Game/Input/IA_Dash.IA_Dash"));
	inputDash = IA_Dash.Object;

	ConstructorHelpers::FObjectFinder<UInputAction> IA_Ability_1(TEXT("/Game/Input/IA_Ability1.IA_Ability1"));
	inputAbility1 = IA_Ability_1.Object;

	ConstructorHelpers::FObjectFinder<UInputAction> IA_Ability_2(TEXT("/Game/Input/IA_Ability2.IA_Ability2"));
	inputAbility2 = IA_Ability_2.Object;

	ConstructorHelpers::FObjectFinder<UInputAction> IA_Ability_3(TEXT("/Game/Input/IA_Ability3.IA_Ability3"));
	inputAbility3 = IA_Ability_3.Object;

	ConstructorHelpers::FObjectFinder<UInputAction> IA_Ability_4(TEXT("/Game/Input/IA_Ability4.IA_Ability4"));
	inputAbility4 = IA_Ability_4.Object;


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector(0, 0, 700.f));
	Camera->SetFieldOfView(90);
	Camera->SetRelativeRotation(FRotator(-90, 0, 0));


	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshOBJ(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	UStaticMesh* Asset = MeshOBJ.Object;
	Cube->SetStaticMesh(Asset);
	Cube->SetRelativeScale3D(FVector(0.25, 0.25, 1.0));
	Cube->SetupAttachment(RootComponent);
	Cube->SetCastShadow(false);
	Cube->SetCollisionProfileName(TEXT("NoCollision"));

	ConstructorHelpers::FObjectFinder<UMaterialInterface> CubeMaterial(TEXT("/Game/Material/MI_White.MI_White"));
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
	Gun->SetCastShadow(false);
	Gun->SetCollisionProfileName(TEXT("NoCollision"));



	ConstructorHelpers::FObjectFinder<UMaterialInterface> GunMaterial(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Material/MI_Orange.MI_Orange'"));
	if (GunMaterial.Succeeded())
	{
		UMaterialInterface* LoadedMat = GunMaterial.Object;
		Gun->SetMaterial(0, LoadedMat);
	}


	BaseCircle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BasePlate"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> BasePlateOBJ(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	UStaticMesh* PlateAsset = BasePlateOBJ.Object;
	BaseCircle->SetStaticMesh(PlateAsset);
	BaseCircle->SetRelativeScale3D(FVector(0.68, 0.68, 0.01));
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
	

	xpSphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("xpCollector"));
	xpSphereCollider->InitSphereRadius(800.f);
	xpSphereCollider->SetupAttachment(Cube);
	xpSphereCollider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	xpSphereCollider->OnComponentBeginOverlap.AddDynamic(this, &APlayer_Background::OnXPOverlapBegin);

	this->SetActorTickInterval(0.01);

	this->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void APlayer_Background::BeginPlay()
{
	Super::BeginPlay();
	PC = Cast<APlayerController>(GetController());

	this->Tags.Add(FName("Player"));

	if (IsValid(PC))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(inputMappingContext, 0);
		}
	}

	if (IsValid(GetCharacterMovement()))
	{
		m_BaseBraking = GetCharacterMovement()->BrakingDecelerationWalking;
		m_BaseFriction = GetCharacterMovement()->GroundFriction;
	}

	GetWorld()->GetTimerManager().SetTimer(mouseLocationTimer, this, &APlayer_Background::MouseLocation, 0.01f, true);
}

// Called to bind functionality to input
void APlayer_Background::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	enhancedInputComponent->BindAction(inputMove, ETriggerEvent::Triggered, this, &APlayer_Background::Move);
	enhancedInputComponent->BindAction(inputDash, ETriggerEvent::Started, this, &APlayer_Background::Dash);
	enhancedInputComponent->BindAction(inputShoot, ETriggerEvent::Triggered, this, &APlayer_Background::Shoot);
	enhancedInputComponent->BindAction(inputAbility1, ETriggerEvent::Started, this, &APlayer_Background::Ability1);
	enhancedInputComponent->BindAction(inputAbility2, ETriggerEvent::Started, this, &APlayer_Background::Ability2);
	enhancedInputComponent->BindAction(inputAbility3, ETriggerEvent::Started, this, &APlayer_Background::Ability3);
	enhancedInputComponent->BindAction(inputAbility4, ETriggerEvent::Started, this, &APlayer_Background::Ability4);

}

void APlayer_Background::Move(const FInputActionValue& Value)
{
	FVector2D movementInput = Value.Get<FVector2D>();

	m_MovementVector.X = GetMesh()->GetForwardVector().X * movementInput.X;
	m_MovementVector.Y = GetMesh()->GetRightVector().Y * movementInput.Y;


	AddMovementInput(m_MovementVector);

}

void APlayer_Background::Shoot(const FInputActionValue& Value)
{
	if (ShootCheck == false)
	{
		GetWorld()->SpawnActor<ABullet_Base>(Gun->GetComponentLocation() + (Gun->GetForwardVector() * 10.f), Gun->GetComponentRotation());
		GetWorld()->GetTimerManager().SetTimer
		(
			ShootTimer, 
			this,
			&APlayer_Background::SetShootCheck,
			ShootCooldown, 
			false 
		);
		ShootCheck = true;
	}
		

	

} 

void APlayer_Background::Dash(const FInputActionValue& Value)
{
	LaunchCharacter(m_MovementVector * 1000, false, false);
}

void APlayer_Background::Ability1(const FInputActionValue& Value)
{
	if (IsValid(Ability1Component))
	{
		Ability1Component->Activation();

	}
}

void APlayer_Background::Ability2(const FInputActionValue& Value)
{
	if (IsValid(Ability2Component))
	{
		Ability2Component->Activation();
	}
}

void APlayer_Background::Ability3(const FInputActionValue& Value)
{
	if (IsValid(Ability3Component))
	{
		Ability3Component->Activation();
	}
}

void APlayer_Background::Ability4(const FInputActionValue& Value)
{
	if (IsValid(Ability4Component))
	{
		Ability4Component->Activation();
	}
}

void APlayer_Background::Damage(float inDamage)
{
	m_HP -= inDamage;
	DeathCheck();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Current HP: %f"), m_HP));

}

void APlayer_Background::IceSurfaceStart(float newFriction, float newBraking)
{
	GetCharacterMovement()->GroundFriction = newFriction;
	GetCharacterMovement()->BrakingDecelerationWalking = newBraking;
}

void APlayer_Background::IceSurfaceEnd()
{
	GetCharacterMovement()->GroundFriction = m_BaseFriction;
	GetCharacterMovement()->BrakingDecelerationWalking = m_BaseBraking;
}

void APlayer_Background::OnXPOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IXP_Interface* Interface = Cast<IXP_Interface>(OtherActor))
	{
		Interface->XPShardMove();
	}

}

void APlayer_Background::MouseLocation()
{
	FHitResult hitResult;
	PC->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, hitResult);
	Cube->SetWorldRotation(FRotator(0, UKismetMathLibrary::FindLookAtRotation(Cube->GetComponentLocation(), hitResult.Location).Yaw,0));
}

void APlayer_Background::DeathCheck()
{
	if (m_HP <= 0)
	{
		UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
	}
}

