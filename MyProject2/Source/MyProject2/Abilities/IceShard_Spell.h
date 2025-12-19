// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/BaseAbilityComponent.h"
#include "Spawnables/IceShard.h"
#include "IceShard_Spell.generated.h"



UCLASS()
class MYPROJECT2_API UIceShard_Spell : public UBaseAbilityComponent
{
	GENERATED_BODY()
	
public:
	void Activation() override;
	void StopAbility() override;
	UIceShard_Spell();
private:
	int numSpawned = 0;
	FTimerHandle SpawnDelayTimer;
	void SpawnShard();
};
