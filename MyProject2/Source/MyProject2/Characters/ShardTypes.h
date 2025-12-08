// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShardTypes.generated.h"


UENUM()
enum class ShardTypes : uint8
{
	Red = 0 UMETA(DisplayName = "Red"),
	Blue = 1 UMETA(DisplayName = "Blue"),
	Green = 2 UMETA(DisplayName = "Green"),
	Purple = 3 UMETA(DIsplayName = "Purple")
};