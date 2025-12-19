// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Meteor_Shower_Spell.h"

void UMeteor_Shower_Spell::Activation()
{
	if (!AbilityCoolDown)
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();

		FHitResult hitResult_Ground;

		PC->GetHitResultUnderCursor(ECC_GameTraceChannel1, false, hitResult_Ground);

		

		if (IsValid(hitResult_Ground.GetActor()))
		{
			spawnLocationCenter = hitResult_Ground.Location;
			GetWorld()->GetTimerManager().SetTimer
			(
				meateorShowerTimer,
				this,
				&UMeteor_Shower_Spell::MeatballSpawn,
				(AbilityDuration - 2) / numToSpawn,
				true
			);
			FTimerHandle cooldownTimer;
			AbilityCoolDown = true;
			GetWorld()->GetTimerManager().SetTimer(cooldownTimer, this, &UMeteor_Shower_Spell::StopAbility, coolDownDuration, false);
		}
	}

}

void UMeteor_Shower_Spell::StopAbility()
{
	SetAbilityReady();
	numSpawned = 0;

}

UMeteor_Shower_Spell::UMeteor_Shower_Spell()
{
	AbilityDuration = 5;
	coolDownDuration = 15.0f;
	numSpawned = 0;

}

void UMeteor_Shower_Spell::MeatballSpawn()
{
	numSpawned++;

	FVector locationToSpawn = FVector(GetPointInCirlce(200.f), 500) + spawnLocationCenter;

	GetWorld()->SpawnActor<AMeatball>(locationToSpawn, FRotator(0, 0, 0));

	if (numSpawned == numToSpawn)
	{
		GetWorld()->GetTimerManager().ClearTimer(meateorShowerTimer);
	}

}
