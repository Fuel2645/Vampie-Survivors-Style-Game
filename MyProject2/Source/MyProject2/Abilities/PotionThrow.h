// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbilityComponent.h"
#include "PotionThrow.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYPROJECT2_API UPotionThrow : public UBaseAbilityComponent
{
	GENERATED_BODY()
	

public:
	virtual void Activation() override;
	virtual void StopAbility() override;
};
