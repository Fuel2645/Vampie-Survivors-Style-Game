// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject2/Abilities/IceShard_Spell.h"

void UIceShard_Spell::Activation()
{
	if (!AbilityCoolDown)
	{
		GetWorld()->GetTimerManager().SetTimer
		(
			SpawnDelayTimer,
			this,
			&UIceShard_Spell::SpawnShard,
			0.2,
			true
		);
		AbilityCoolDown = true;
	}
}

void UIceShard_Spell::StopAbility()
{
	SetAbilityReady();
	numSpawned = 0;
}

UIceShard_Spell::UIceShard_Spell()
{
	AbilityDuration = 4.0f;
}

void UIceShard_Spell::SpawnShard()
{
	for (UActorComponent* comp : GetWorld()->GetFirstPlayerController()->GetPawn()->GetComponents())
	{
		if (comp->GetFName() == FName("Gun"))
		{
			numSpawned++;
			AIceShard* IceShard = GetWorld()->SpawnActor<AIceShard>();
			switch (numSpawned)
			{
			case 1:
				IceShard->AttachToComponent(Cast<USceneComponent>(comp), FAttachmentTransformRules::KeepRelativeTransform);
				IceShard->SetActorLocation(Cast<USceneComponent>(comp)->GetComponentLocation() + Cast<USceneComponent>(comp)->GetRightVector() * 60);
				break;
			case 2:
				IceShard->AttachToComponent(Cast<USceneComponent>(comp), FAttachmentTransformRules::KeepRelativeTransform);
				IceShard->SetActorLocation(Cast<USceneComponent>(comp)->GetComponentLocation() + Cast<USceneComponent>(comp)->GetRightVector() * -60);
				break;
			case 3:
				IceShard->AttachToComponent(Cast<USceneComponent>(comp), FAttachmentTransformRules::KeepRelativeTransform);
				IceShard->SetActorLocation(Cast<USceneComponent>(comp)->GetComponentLocation() + Cast<USceneComponent>(comp)->GetUpVector() * 30);
				GetWorld()->GetTimerManager().ClearTimer(SpawnDelayTimer);
				GetWorld()->GetTimerManager().SetTimer(DurationTimer, this, &UIceShard_Spell::StopAbility, AbilityDuration, false);
				break;
			default:
				break;
			}
		}
	}
}
