// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYPROJECT2_API IPlayerInteractionInterface
{
	GENERATED_BODY()
public:
	virtual void Damage(float inDamage);
	virtual void IceSurfaceStart(float newFriction, float newBraking);
	virtual void IceSurfaceEnd();


	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
