// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UnitInteraction.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUnitInteraction : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYPROJECT2_API IUnitInteraction
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Damage(float inDamage);
	virtual void PoisonDamageStart(float inDamage, float TimeBetween);
	virtual void PoisonDamageEnd();
	virtual void FireDamageStart(float inDamage, float TimeBetween);
	virtual void FireDamageEnd();
	virtual void SlowStart(float Duration, float slowPercentage);
	virtual void SlowEnd();
	virtual void StunStart(float Duration);
	virtual void StunEnd();

};
