// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/BaseAbilityComponent.h"
#include "Spawnables/BrokenGround.h"
#include "BrokenGround_Spell.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UBrokenGround_Spell : public UBaseAbilityComponent
{
	GENERATED_BODY()

public:
	void Activation() override;
	void StopAbility() override;
	UBrokenGround_Spell();
	
private:
	ABrokenGround* brokenGround;
	
};
