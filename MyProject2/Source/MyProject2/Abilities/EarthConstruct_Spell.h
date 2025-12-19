// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/BaseAbilityComponent.h"
#include "Characters/EarthConstruct.h"
#include "EarthConstruct_Spell.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UEarthConstruct_Spell : public UBaseAbilityComponent
{
	GENERATED_BODY()
	

public:
	void Activation() override;
	void StopAbility() override;
	UEarthConstruct_Spell();
private:

};
