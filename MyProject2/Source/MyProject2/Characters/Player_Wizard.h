// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject2/Characters/Player_Background.h"
#include "MyProject2/WizardStates.h"
#include "MyProject2/Abilities/Wall_Spell.h"
#include "MyProject2/Abilities/Meteor_Shower_Spell.h"
#include "MyProject2/Abilities/IceBeem_Spell.h"
#include "MyProject2/Abilities/IceShard_Spell.h"
#include "MyProject2/Abilities/iceFloor_Spell.h"
#include "MyProject2/Abilities/FireFloor_Spell.h"
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
	UBaseAbilityComponent* IceGroundGround_Spell;
	UBaseAbilityComponent* FireFireFire_Spell; //done
	UBaseAbilityComponent* FireFireGround_Spell;  //done
	UBaseAbilityComponent* FireGroundGround_Spell;
	UBaseAbilityComponent* FireGroundIce_Spell;

	TArray<FString> m_Inputs;
	bool ShootCheck;

	TArray<UStaticMeshComponent*> visualBalls;

	void ballAnimation();
	int curBallNum=0;

	TSoftObjectPtr<UMaterialInterface> iceBallmatRef;
	TSoftObjectPtr<UMaterialInterface> fireBallmatRef;
	TSoftObjectPtr<UMaterialInterface> groundBallmatRef;
};
