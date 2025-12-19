// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/RotatingBallsAbility.h"



void URotatingBallsAbility::Activation()
{
	GetWorld()->GetTimerManager().SetTimer(
		DurationTimer,
		this,
		&URotatingBallsAbility::StopAbility,
		AbilityDuration,
		false
	);

	if (DoOnce)
	{
	}
	else
	{
		DoOnce = true;
		TArray<FVector> Temp;

		if (!Temp.IsEmpty())
			Temp.Empty();



		Temp.Init(FVector(0, 0, 0), ballCount);

		Temp[0] = GetOwner()->GetActorForwardVector() * 150.f;
		Temp[0].Z = 0;

		ARotatingBall* tempBall = GetWorld()->SpawnActor<ARotatingBall>(FVector(0, 0, 0), FRotator(0, 0, 0));
		tempBall->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepRelativeTransform);
		tempBall->SetActorRelativeLocation(Temp[0]);
		tempBall->SetActorScale3D(FVector(0.5, 0.5, 0.5));

		m_Balls.Emplace(tempBall);

		double Angle = (360 / ballCount) * (PI / 180);

		for (int x = 1; x < Temp.Num(); x++)
		{
			Temp[x] = FVector(Temp[x - 1].X * cos(Angle) - Temp[x - 1].Y * sin(Angle), (Temp[x - 1].X * sin(Angle) + Temp[x - 1].Y * cos(Angle)), 0);
			ARotatingBall* TemptempBall = GetWorld()->SpawnActor<ARotatingBall>(FVector(0, 0, 0), FRotator(0, 0, 0));
			TemptempBall->SetActorRelativeLocation(Temp[x]);
			TemptempBall->SetActorScale3D(FVector(0.5, 0.5, 0.5));
			TemptempBall->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepRelativeTransform);
			m_Balls.Emplace(TemptempBall);
		}
	}



}


void URotatingBallsAbility::StopAbility()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Numof Balls %f"), float(m_Balls.Num())));

	for (ARotatingBall* currentBall : m_Balls)
	{
		if (IsValid(currentBall))
			currentBall->Destroy();
	}

	m_Balls.Empty();
	DoOnce = false;
}

URotatingBallsAbility::URotatingBallsAbility()
	:UBaseAbilityComponent()
{
}

URotatingBallsAbility::URotatingBallsAbility(float GivenAbilityDuration, int GivenBallCount)
	: UBaseAbilityComponent(GivenAbilityDuration)
{
	ballCount = GivenBallCount;
}
