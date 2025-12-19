// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Bullet_Base.h"
#include "Bullet_Rebound.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API ABullet_Rebound : public ABullet_Base
{
	GENERATED_BODY()

protected:
	virtual void Movement() override;



private:
	uint8 movementCount;

public:
	virtual void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	) override;

};
