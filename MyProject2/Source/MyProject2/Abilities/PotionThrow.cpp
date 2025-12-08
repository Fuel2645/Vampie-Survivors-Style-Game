// Fill out your copyright notice in the Description page of Project Settings.

#include "PotionThrow.h"
#include "MyProject2/Spawnables/PoisonPool.h"


void UPotionThrow::Activation()
{
	USceneComponent* gunComponent = GetOwner()->GetRootComponent();

	for (UActorComponent* comp : GetOwner()->GetComponents())
	{
		if (comp->GetFName() == FName("Gun"))
		{
			gunComponent = Cast<USceneComponent>(comp);
		}
	}

	FVector TraceStart = GetOwner()->GetActorLocation() + gunComponent->GetForwardVector() * 300.0f;
	TraceStart.Z = 5000.f;

	FVector TraceEnd = GetOwner()->GetActorLocation() + gunComponent->GetForwardVector() * 300.0f;
	TraceEnd.Z = -10.f;

	FHitResult hitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel
	(
		hitResult,
		TraceStart,
		TraceEnd,
		ECollisionChannel::ECC_GameTraceChannel1,
		QueryParams

	);

	if (IsValid(hitResult.GetActor()))
	{
		GetWorld()->SpawnActor<APoisonPool>(hitResult.Location + FVector(0,0,3), FRotator(0, 0, 0));
	}
	



}

void UPotionThrow::StopAbility()
{
}
