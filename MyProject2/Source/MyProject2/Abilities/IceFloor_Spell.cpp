// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/IceFloor_Spell.h"

void UIceFloor_Spell::Activation()
{
	if (!AbilityCoolDown)
	{
		FHitResult hitResult;

		APlayerController* playerController = GetWorld()->GetFirstPlayerController();

		playerController->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, hitResult);

		if (IsValid(hitResult.GetActor()))
		{
			iceFloorActor = GetWorld()->SpawnActor<AiceFloor>(hitResult.Location, FRotator(0, 0, 0));
			AbilityCoolDown = true;
			GetWorld()->GetTimerManager().SetTimer(
				DurationTimer,
				this,
				&UIceFloor_Spell::StopAbility,
				AbilityDuration,
				false
			);
		}
	}
}

void UIceFloor_Spell::StopAbility()
{
	SetAbilityReady();
	iceFloorActor->Destroy();

}

UIceFloor_Spell::UIceFloor_Spell()
{
	AbilityDuration = 10.0f;
}
