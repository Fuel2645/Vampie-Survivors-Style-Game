// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject2/Abilities/Wall_Spell.h"

void UWall_Spell::Activation()
{
	if (!AbilityCoolDown)
	{
		USceneComponent* gunComponent = GetOwner()->GetRootComponent();

		for (UActorComponent* comp : GetOwner()->GetComponents())
		{
			if (comp->GetFName() == FName("Gun"))
			{
				gunComponent = Cast<USceneComponent>(comp);
			}
		}

		AbilityDuration = 5.0f;

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Activation")));


		FHitResult hitResult;

		APlayerController* playerController = GetWorld()->GetFirstPlayerController();

		playerController->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, hitResult);

		if (IsValid(hitResult.GetActor()))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Hit Result")));

			FRotator rotation = FRotator(UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), hitResult.Location));
			rotation.Roll = 0;
			rotation.Pitch = 0;
			AWall* wall = GetWorld()->SpawnActor<AWall>(hitResult.Location + FVector(0, 0, 3), rotation);
			wall->Initalise(5, hitResult.Location, rotation);


			GetWorld()->GetTimerManager().SetTimer
			(
				DurationTimer,
				this,
				&UWall_Spell::SetAbilityReady,
				AbilityDuration,
				false
			);

			AbilityCoolDown = true;
		}



	}
}

void UWall_Spell::StopAbility()
{
}
