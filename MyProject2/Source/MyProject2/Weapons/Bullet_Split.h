// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Bullet_Base.h"
#include "Bullet_Split.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API ABullet_Split : public ABullet_Base
{
	GENERATED_BODY()
	

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
