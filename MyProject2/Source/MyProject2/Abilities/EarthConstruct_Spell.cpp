// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/EarthConstruct_Spell.h"

void UEarthConstruct_Spell::Activation()
{
	if (!AbilityCoolDown)
	{
		FHitResult hitResult;

		APlayerController* playerController = GetWorld()->GetFirstPlayerController();

		playerController->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, hitResult);

		if (IsValid(hitResult.GetActor()))
		{
			GetWorld()->SpawnActor<AEarthConstruct>(hitResult.Location, FRotator(0, 0, 0));
			AbilityCoolDown = true;
			GetWorld()->GetTimerManager().SetTimer(CooldownTimer, this, &UEarthConstruct_Spell::SetAbilityReady, AbilityCooldownDuration, false);
		}
	}

}

void UEarthConstruct_Spell::StopAbility()
{
}

UEarthConstruct_Spell::UEarthConstruct_Spell()
{
	AbilityCooldownDuration = 30.0f;


}
