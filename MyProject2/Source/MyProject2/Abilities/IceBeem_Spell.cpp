// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/IceBeem_Spell.h"

void UIceBeem_Spell::Activation()
{
	if (!AbilityCoolDown)
	{
		for (UActorComponent* comp : GetWorld()->GetFirstPlayerController()->GetPawn()->GetComponents())
		{
			if (comp->GetFName() == FName("Gun"))
			{
				MikuBeam = GetWorld()->SpawnActor<AIceBeam>();
				MikuBeam->AttachToComponent(Cast<USceneComponent>(comp), FAttachmentTransformRules::KeepRelativeTransform);
			}
		}

		GetWorld()->GetTimerManager().SetTimer
		(
			DurationTimer,
			this,
			&UIceBeem_Spell::StopAbility,
			AbilityDuration-1,
			false
		);
		AbilityCoolDown = true;
	}
}

void UIceBeem_Spell::StopAbility()
{
	MikuBeam->Destroy();

	GetWorld()->GetTimerManager().SetTimer
	(
		DurationTimer,
		this,
		&UIceBeem_Spell::SetAbilityReady,
		1,
		false
	);
}

UIceBeem_Spell::UIceBeem_Spell()
{
	AbilityDuration = 3.0f;
}
