// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/CleaveAbility.h"


void UCleaveAbility::Activation()
{

	USceneComponent* gunComponent = GetOwner()->GetRootComponent();

	for (UActorComponent* comp : GetOwner()->GetComponents())
	{
		if (comp->GetFName() == FName("Gun"))
		{
			gunComponent = Cast<USceneComponent>(comp);
		}
	}

	if (gunComponent == nullptr)
	{

	}
	else
	{
		const FName TraceTag("CleaveTag");
		GetWorld()->DebugDrawTraceTag = TraceTag;



		FHitResult hitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(GetOwner());
		QueryParams.TraceTag = TraceTag;

		FVector TraceStart;
		FVector TraceEnd;

		float CleaveOffset;

		CleaveOffset = (180 - CleaveRadius) / 2;


		TraceStart = GetOwner()->GetRootComponent()->GetComponentLocation();





		if (RLCheck) 
		{
			for (int x = 0; x <= LineTraceCount; x++)
			{
				TraceEnd = GetOwner()->GetRootComponent()->GetComponentLocation() - (gunComponent->GetRightVector() * SwordLength).RotateAngleAxis(CleaveOffset + (CleaveRadius / LineTraceCount) * x, FVector(0, 0, 1));
				GetWorld()->LineTraceSingleByChannel
				(
					hitResult,
					TraceStart,
					TraceEnd,
					ECollisionChannel::ECC_Visibility,
					QueryParams
				);

				

				if (IsValid(hitResult.GetActor()))
				{
					if (IUnitInteraction* Interface = Cast<IUnitInteraction>(hitResult.GetActor()))
					{
						Interface->Damage(20.f);
					}

				}
			}

			GetWorld()->GetTimerManager().ClearTimer(RLResetTimer);
			GetWorld()->GetTimerManager().SetTimer
			(
				RLResetTimer,
				this,
				&UCleaveAbility::RLReset,
				0.4,
				false
			);

			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Right Left");
		}
		else
		{
			for (int x = 0; x <= LineTraceCount; x++)
			{
				TraceEnd = GetOwner()->GetRootComponent()->GetComponentLocation() - (gunComponent->GetRightVector() * -SwordLength).RotateAngleAxis(CleaveOffset + (CleaveRadius / LineTraceCount) * x, FVector(0, 0, -1));
				GetWorld()->LineTraceSingleByChannel
				(
					hitResult,
					TraceStart,
					TraceEnd,
					ECollisionChannel::ECC_Visibility,
					QueryParams
				);

				if (IsValid(hitResult.GetActor()))
				{
					if (IUnitInteraction* Interface = Cast<IUnitInteraction>(hitResult.GetActor()))
					{
						Interface->Damage(20.f);
					}

				}
			}
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, "Left Right");
		}
		RLCheck = !RLCheck;
		SwordLength += 50;
	}
	
	
	
	
	
}

void UCleaveAbility::StopAbility()
{
}

void UCleaveAbility::RLReset()
{
	RLCheck = true;
}
