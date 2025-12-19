// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/BasicProjectile_Spell.h"

void UBasicProjectile_Spell::Activation()
{
	if (!AbilityCoolDown)
	{
		for (UActorComponent* comp : GetWorld()->GetFirstPlayerController()->GetPawn()->GetComponents())
		{
			if (comp->GetFName() == FName("Gun"))
			{
				GetWorld()->SpawnActor<ABullet_Base>(Cast<USceneComponent>(comp)->GetComponentLocation(), Cast<USceneComponent>(comp)->GetComponentRotation());
				break;
			}
		}

		GetWorld()->GetTimerManager().SetTimer(CooldownTimer, this, &UBasicProjectile_Spell::SetAbilityReady, AbilityCooldownDuration, false);
	}
}

void UBasicProjectile_Spell::StopAbility()
{
}

UBasicProjectile_Spell::UBasicProjectile_Spell()
{
	AbilityCooldownDuration = 1.0f;
}
