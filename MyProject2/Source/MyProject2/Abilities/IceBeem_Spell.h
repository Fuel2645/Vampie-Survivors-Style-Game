// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject2/Abilities/BaseAbilityComponent.h"
#include "MyProject2/Spawnables/IceBeam.h"
#include "IceBeem_Spell.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UIceBeem_Spell : public UBaseAbilityComponent
{
	GENERATED_BODY()
	
public:
	void Activation() override;
	void StopAbility() override;
	UIceBeem_Spell();
private:
	FTimerHandle beamTimer;
	AIceBeam* MikuBeam;
};
