// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player_Wizard.h"
#include "Weapons/Bullet_Split.h"

void APlayer_Wizard::Shoot(const FInputActionValue& Value)
{
	TArray<FString> TempArray = m_Inputs;
	TempArray.Sort();

	FString sortedOrder;
	for (FString& name : TempArray)
	{
		sortedOrder.Append(name);
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, FString::Printf(TEXT("Shoot")));


	if (ShootCheck == false)
	{
		if (sortedOrder == "GGG")  //3 Ground
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Silver, FString::Printf(TEXT("EE")));
			if (IsValid(GroundGroundGround_Spell))
			{
				GroundGroundGround_Spell->Activation();
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("COmponentn Invalid")));
			}
		}
		else if (sortedOrder == "FGG") //2Ground 1 Fire
		{
			if (IsValid(FireGroundGround_Spell))
			{
				FireGroundGround_Spell->Activation();
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("COmponentn Invalid")));
			}
		}
		else if (sortedOrder == "FFG") // 2Fire 1 Ground
		{
			if (IsValid(FireFireGround_Spell))
			{
				FireFireGround_Spell->Activation();
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("COmponentn Invalid")));
			}
		}
		else if (sortedOrder == "GGI") //2Ground 1 Ice
		{
			if (IsValid(IceGroundGround_Spell))
			{
				IceGroundGround_Spell->Activation();
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("COmponentn Invalid")));
			}
		}
		else if (sortedOrder == "GII") //2Ice 1 Ground
		{
			if (IsValid(IceIceGround_Spell))
			{
				IceIceGround_Spell->Activation();
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("COmponentn Invalid")));
			}
		}
		else if (sortedOrder == "FGI") //Trio
		{
			if (IsValid(FireGroundIce_Spell))
			{
				FireGroundIce_Spell->Activation();
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("COmponentn Invalid")));
			}
		}
		else if (sortedOrder == "III") //3 Ice
		{
			if (IsValid(IceIceIce_Spell))
			{
				IceIceIce_Spell->Activation();
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("COmponentn Invalid")));
			}
		}
		else if (sortedOrder == "FII") //2Ice 1 Fire
		{
			if (IsValid(IceIceFire_Spell))
			{
				IceIceFire_Spell->Activation();
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("COmponentn Invalid")));
			}
		}
		else if (sortedOrder == "FFI") //2Fire 1 Ice
		{
			if (IsValid(IceFireFire_Spell))
			{
				IceFireFire_Spell->Activation();
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("COmponentn Invalid")));
			}
		}
		else if (sortedOrder == "FFF") //3 Fire
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("WWW")));
			if (IsValid(FireFireFire_Spell))
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Meatball")));
				FireFireFire_Spell->Activation();
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("COmponentn Invalid")));
			}
		}

		GetWorld()->GetTimerManager().SetTimer
		(
			ShootTimer,
			this,
			&APlayer_Wizard::SetShootCheckHelp,
			ShootCooldown,
			false
		);
		ShootCheck = true;
	}

}

void APlayer_Wizard::Ability1(const FInputActionValue& Value)
{
	if (m_Inputs.Num() == 3)
	{
		m_Inputs.RemoveAt(2);
	}
	else
	{
		visualBalls[curBallNum]->SetHiddenInGame(false);
	}
	m_Inputs.Insert("I", 0);
	UAssetManager::GetStreamableManager().RequestAsyncLoad
	(
		iceBallmatRef.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda([this]()
			{
				UMaterialInterface* loadedMat = iceBallmatRef.Get();
				visualBalls[curBallNum]->SetMaterial(0, loadedMat);
			})
	);
	if (curBallNum == 2)
	{
		curBallNum = 0;
	}
	else
	{
		curBallNum++;
	}
}

void APlayer_Wizard::Ability2(const FInputActionValue& Value)
{
	if (m_Inputs.Num() == 3)
	{
		m_Inputs.RemoveAt(2);
	}
	else
	{
		visualBalls[curBallNum]->SetHiddenInGame(false);
	}
	m_Inputs.Insert("F", 0);
	UAssetManager::GetStreamableManager().RequestAsyncLoad
	(
		fireBallmatRef.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda([this]()
			{
				UMaterialInterface* loadedMat = fireBallmatRef.Get();
				visualBalls[curBallNum]->SetMaterial(0, loadedMat);
			})
	);
	if (curBallNum == 2)
	{
		curBallNum = 0;
	}
	else
	{
		curBallNum++;
	}
}

void APlayer_Wizard::Ability3(const FInputActionValue& Value)
{
	if (m_Inputs.Num() == 3)
	{
		m_Inputs.RemoveAt(2);
	}
	else
	{
		visualBalls[curBallNum]->SetHiddenInGame(false);
	}
	m_Inputs.Insert("G", 0);
	UAssetManager::GetStreamableManager().RequestAsyncLoad
	(
		groundBallmatRef.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda([this]()
			{
				UMaterialInterface* loadedMat = groundBallmatRef.Get();
				visualBalls[curBallNum]->SetMaterial(0, loadedMat);
			})
	);
	if (curBallNum == 2)
	{
		curBallNum = 0;
	}
	else
	{
		curBallNum++;
	}
}

void APlayer_Wizard::Ability4(const FInputActionValue& Value)
{
}

APlayer_Wizard::APlayer_Wizard()
{ 
	GroundGroundGround_Spell = CreateDefaultSubobject<UWall_Spell>(TEXT("GGG"));
	FireFireFire_Spell = CreateDefaultSubobject<UMeteor_Shower_Spell>(TEXT("FFF"));
	IceIceIce_Spell = CreateDefaultSubobject<UIceBeem_Spell>(TEXT("III"));
	IceIceFire_Spell = CreateDefaultSubobject<UIceShard_Spell>(TEXT("IIF"));
	IceIceGround_Spell = CreateDefaultSubobject<UIceFloor_Spell>(TEXT("IIG"));
	FireFireGround_Spell = CreateDefaultSubobject<UFireFloor_Spell>(TEXT("FFG"));
	IceGroundGround_Spell = CreateDefaultSubobject<UBrokenGround_Spell>(TEXT("IGG"));
	FireGroundIce_Spell = CreateDefaultSubobject<UBasicProjectile_Spell>(TEXT("FGI"));
	FireGroundGround_Spell = CreateDefaultSubobject<UEarthConstruct_Spell>(TEXT("FGG"));
	IceFireFire_Spell = CreateDefaultSubobject<URotatingBallsAbility>(TEXT("IFF"));

	/*
	
	
	*/

	ConstructorHelpers::FObjectFinder<UMaterialInterface> MeshMaterial(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Material/MI_Orange.MI_Orange'"));
	UMaterialInterface* LoadedMat = MeshMaterial.Object;
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshOBJ(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	UStaticMesh* Asset = MeshOBJ.Object;





	for(int x = 1; x < 4; x++)
	{
		FName ballName(*FString::Printf(TEXT("Ball_%d"), x));

		UStaticMeshComponent* ball = CreateDefaultSubobject<UStaticMeshComponent>(ballName);
		ball->SetupAttachment(RootComponent);
		ball->SetStaticMesh(Asset);
		ball->SetMaterial(0, LoadedMat);
		ball->SetCollisionProfileName(TEXT("NoCollision"));
		ball->SetWorldScale3D(FVector(0.3, 0.3, 0.3));
		ball->SetCastShadow(false);
		ball->SetHiddenInGame(true);
		visualBalls.Add(ball);
	}

	
	double Angle = (360 / 3) * (PI / 180);

	TArray<FVector> Temp;

	if (!Temp.IsEmpty())
		Temp.Empty();



	Temp.Init(FVector(0, 0, 0), 3);

	Temp[0] = Cube->GetRelativeLocation() + Cube->GetUpVector() * 35.f + Cube->GetForwardVector() * 40.f;
	visualBalls[0]->SetRelativeLocation(Temp[0]);

	for (int x = 1; x < visualBalls.Num(); x++)
	{
		Temp[x] = FVector(Temp[x - 1].X * cos(Angle) - Temp[x - 1].Y * sin(Angle), (Temp[x - 1].X * sin(Angle) + Temp[x - 1].Y * cos(Angle)), Cube->GetUpVector().Z * 35.f);
		visualBalls[x]->SetRelativeLocation(Temp[x]);
	}

	iceBallmatRef = TSoftObjectPtr<UMaterialInterface>(FSoftObjectPath(TEXT("/Game/Material/MI_Ice_Gradiant.MI_Ice_Gradiant")));
	fireBallmatRef = TSoftObjectPtr<UMaterialInterface>(FSoftObjectPath(TEXT("/Game/Material/MI_Fire_Gradiant.MI_Fire_Gradiant")));
	groundBallmatRef = TSoftObjectPtr<UMaterialInterface>(FSoftObjectPath(TEXT("/Game/Material/MI_Ground_Gradiant.MI_Ground_Gradiant")));


}

void APlayer_Wizard::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle visualBallTimer;

	GetWorld()->GetTimerManager().SetTimer
	(
		visualBallTimer,
		this,
		&APlayer_Wizard::ballAnimation,
		0.01f,
		true
	);

}

void APlayer_Wizard::ballAnimation()
{
	for (UStaticMeshComponent* mesh : visualBalls)
	{
		mesh->SetRelativeLocation(mesh->GetRelativeLocation().RotateAngleAxis(2.f, FVector(0, 0, 1)));
	}

}
