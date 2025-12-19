// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/BaseAbilityComponent.h"
#include "Spawnables/Wall.h"
#include "Kismet/KismetMathLibrary.h"
#include "Wall_Spell.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYPROJECT2_API UWall_Spell : public UBaseAbilityComponent
{
	GENERATED_BODY()
	
public:
	virtual void Activation() override;
	virtual void StopAbility() override;



};
