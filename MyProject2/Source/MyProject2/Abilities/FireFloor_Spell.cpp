// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject2/Abilities/FireFloor_Spell.h"

void UFireFloor_Spell::Activation()
{
	if (!AbilityCoolDown)
	{
		
		fireFloorRef = GetWorld()->SpawnActor<AFireFloor>(this->GetOwner()->GetActorLocation()- FVector(0,0,50), FRotator(0, 0, 0));
		GetWorld()->GetTimerManager().SetTimer(DurationTimer, this, &UFireFloor_Spell::StopAbility, AbilityDuration, false);
		GetWorld()->GetTimerManager().SetTimer(CooldownTimer, this, &UFireFloor_Spell::SetAbilityReady, AbilityCooldownDuration, false);
		AbilityCoolDown = true;
	}

}

void UFireFloor_Spell::StopAbility()
{
	fireFloorRef->Destroy();

}

UFireFloor_Spell::UFireFloor_Spell()
{
	AbilityDuration = 5.0f;
	AbilityCooldownDuration = 20.0f;

}
