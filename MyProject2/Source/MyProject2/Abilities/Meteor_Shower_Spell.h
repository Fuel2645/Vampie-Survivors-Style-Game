// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject2/Abilities/BaseAbilityComponent.h"
#include "MyProject2/Spawnables/Meatball.h"
#include "Meteor_Shower_Spell.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UMeteor_Shower_Spell : public UBaseAbilityComponent
{
	GENERATED_BODY()
	

public:
	virtual void Activation() override;
	virtual void StopAbility() override;

	UMeteor_Shower_Spell();
private:
	FTimerHandle meateorShowerTimer;

	void MeatballSpawn();
	FVector spawnLocationCenter = FVector(0,0,0);
	int numToSpawn = 10;
	int numSpawned = 0;
	float coolDownDuration;

};
