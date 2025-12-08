// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject2/Abilities/BaseAbilityComponent.h"
#include "MyProject2/Interfaces/UnitInteraction.h"
#include "CleaveAbility.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYPROJECT2_API UCleaveAbility : public UBaseAbilityComponent
{
	GENERATED_BODY()
	

public:
	virtual void Activation() override;
	virtual void StopAbility() override;


private:
	UPROPERTY(EditAnywhere, Category = "Collision")
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Visibility;
	int LineTraceCount = 10;
	int CleaveRadius = 110;
	float SwordLength =100.f;
	bool RLCheck = true;

	FTimerHandle RLResetTimer;

	void RLReset();

};
