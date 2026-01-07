// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Characters/ShardTypes.h"
#include "ST_Enemy.generated.h"


USTRUCT(BlueprintType)
struct FST_EnemyDataRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	ShardTypes ShardType;

	UPROPERTY(EditAnywhere)
	float HP;

	UPROPERTY(EditAnywhere)
	UMaterialInstance* Colour;

	UPROPERTY(EditAnywhere)
	FVector size;

	UPROPERTY(EditAnywhere)
	float Speed;

	UPROPERTY(EditAnywhere)
	float Damage;

};
