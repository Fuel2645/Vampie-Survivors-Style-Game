// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject2/Abilities/BaseAbilityComponent.h"
#include "MyProject2/Spawnables/FireFloor.h"
#include "FireFloor_Spell.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UFireFloor_Spell : public UBaseAbilityComponent
{
	GENERATED_BODY()

public:
	void Activation() override;
	void StopAbility() override;

	UFireFloor_Spell();


private:
	AFireFloor* fireFloorRef;
};
