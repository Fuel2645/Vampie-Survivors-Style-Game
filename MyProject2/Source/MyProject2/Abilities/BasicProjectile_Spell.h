// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/BaseAbilityComponent.h"
#include "Weapons/Bullet_Base.h"
#include "BasicProjectile_Spell.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UBasicProjectile_Spell : public UBaseAbilityComponent
{
	GENERATED_BODY()
	
public:
	void Activation() override;
	void StopAbility() override;
	UBasicProjectile_Spell();
};
