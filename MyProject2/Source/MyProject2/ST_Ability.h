// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Abilities/BaseAbilityComponent.h"
#include "ST_Ability.generated.h"


USTRUCT(BlueprintType)
struct FST_Ability : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UBaseAbilityComponent> AbilityComponent;

	UPROPERTY(EditAnywhere)
	float Cooldown;

	UPROPERTY(EditAnywhere)
	float Duration;

	UPROPERTY(EditAnywhere)
	float Damage;

	UPROPERTY(EditAnywhere) //WIll cahnge represent unique upgradses per abiulity 
	int UniqueInt;

	UPROPERTY(EditAnywhere)
	float UniqueFloat;


};
