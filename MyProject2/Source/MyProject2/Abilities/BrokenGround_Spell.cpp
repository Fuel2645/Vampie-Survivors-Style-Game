// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/BrokenGround_Spell.h"

void UBrokenGround_Spell::Activation()
{
	if (!AbilityCoolDown)
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();

		FHitResult hitResult_Ground;

		PC->GetHitResultUnderCursor(ECC_GameTraceChannel1, false, hitResult_Ground);



		if (IsValid(hitResult_Ground.GetActor()))
		{
			FVector locationToSpawn = (hitResult_Ground.Location - FVector(0, 0, 100));
			brokenGround = GetWorld()->SpawnActor<ABrokenGround>();
			brokenGround->SetActorLocation(locationToSpawn);
			AbilityCoolDown = true;
			GetWorld()->GetTimerManager().SetTimer(CooldownTimer, this, &UBrokenGround_Spell::SetAbilityReady, AbilityCooldownDuration, false);
			GetWorld()->GetTimerManager().SetTimer(DurationTimer, this, &UBrokenGround_Spell::StopAbility, AbilityCoolDown, false);
		}
	}
}

void UBrokenGround_Spell::StopAbility()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Destroyed grouynd")));
	brokenGround->Destroy();
	brokenGround = nullptr;
}

UBrokenGround_Spell::UBrokenGround_Spell()
{
	AbilityDuration = 1.2f;
	AbilityCooldownDuration = 10.f;
}
