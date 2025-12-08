// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbilityComponent.h"
#include "RotatingBall.h"
#include "RotatingBallsAbility.generated.h"
/**
 * 
 */


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYPROJECT2_API URotatingBallsAbility : public UBaseAbilityComponent
{
	GENERATED_BODY()
	

public:
	virtual void Activation() override; 
	virtual void StopAbility() override;
	
	URotatingBallsAbility();
	URotatingBallsAbility(float GivenAbilityDuration, int GivenBallCount);

	int ballCount = 3;


private:
	TArray<ARotatingBall*> m_Balls;
	bool DoOnce = false;

};
