// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Bullet_Split.h"

void ABullet_Split::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IUnitInteraction* Interface = Cast<IUnitInteraction>(OtherActor))
	{
		if (!overlappingActors.Contains(OtherActor))
		{
			Interface->Damage(m_Damage);
			GetWorld()->SpawnActor<ABullet_Base>(this->GetActorLocation(), this->GetActorRotation() + FRotator(0, 45, 0));
			GetWorld()->SpawnActor<ABullet_Base>(this->GetActorLocation(), this->GetActorRotation() - FRotator(0, 45, 0));
			this->Destroy();
		}
		
	}
}
