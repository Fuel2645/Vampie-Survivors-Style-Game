// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Player_Background.h"
#include "WizardStates.h"
#include "Abilities/Wall_Spell.h"
#include "Abilities/Meteor_Shower_Spell.h"
#include "Abilities/IceBeem_Spell.h"
#include "Abilities/IceShard_Spell.h"
#include "Abilities/iceFloor_Spell.h"
#include "Abilities/FireFloor_Spell.h"
#include "Abilities/BrokenGround_Spell.h"
#include "Abilities/BasicProjectile_Spell.h"
#include "Abilities/EarthConstruct_Spell.h"
#include "Abilities/RotatingBallsAbility.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Player_Wizard.generated.h"

 

UCLASS()
class MYPROJECT2_API APlayer_Wizard : public APlayer_Background
{
	GENERATED_BODY()

public:
	void Shoot(const FInputActionValue& Value) override;
	void Ability1(const FInputActionValue& Value) override;
	void Ability2(const FInputActionValue& Value) override;
	void Ability3(const FInputActionValue& Value) override;
	void Ability4(const FInputActionValue& Value) override;

	void SetShootCheckHelp() { ShootCheck = false; };

	APlayer_Wizard();
	virtual void BeginPlay() override;
protected:

private:
	WizardStates m_State;

	UBaseAbilityComponent* GroundGroundGround_Spell; //done
	UBaseAbilityComponent* IceIceIce_Spell; //done
	UBaseAbilityComponent* IceIceFire_Spell; //done
	UBaseAbilityComponent* IceFireFire_Spell;
	UBaseAbilityComponent* IceIceGround_Spell; //done
	UBaseAbilityComponent* IceGroundGround_Spell; //done
	UBaseAbilityComponent* FireFireFire_Spell; //done
	UBaseAbilityComponent* FireFireGround_Spell;  //done
	UBaseAbilityComponent* FireGroundGround_Spell; //done
	UBaseAbilityComponent* FireGroundIce_Spell; //done

	TArray<FString> m_Inputs;
	bool ShootCheck;

	TArray<UStaticMeshComponent*> visualBalls;

	void ballAnimation();
	int curBallNum=0;

	TSoftObjectPtr<UMaterialInterface> iceBallmatRef;
	TSoftObjectPtr<UMaterialInterface> fireBallmatRef;
	TSoftObjectPtr<UMaterialInterface> groundBallmatRef;
};
