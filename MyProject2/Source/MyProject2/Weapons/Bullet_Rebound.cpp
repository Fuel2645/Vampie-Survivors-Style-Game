// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Bullet_Rebound.h"

void ABullet_Rebound::Movement()
{
	if (movementCount < 40)
	{
		movementCount++;
	}
	else
	{
		FVector Direction = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - this->GetActorLocation();
		this->SetActorRotation(FMath::RInterpTo(this->GetActorRotation(), Direction.Rotation(), GetWorld()->GetDeltaSeconds(), 90.f));
	}
	this->SetActorLocation(this->GetActorLocation() + this->GetActorForwardVector() * m_MovementSpeed);
}

void ABullet_Rebound::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetWorld()->GetFirstPlayerController()->GetPawn() && movementCount >= 40)
	{
		this->Destroy();
	}
	else if (IUnitInteraction* Interface = Cast<IUnitInteraction>(OtherActor))
	{
		if (!overlappingActors.Contains(OtherActor))
		{
			Interface->Damage(m_Damage);
			overlappingActors.Add(OtherActor);
		}
	}
	

}
