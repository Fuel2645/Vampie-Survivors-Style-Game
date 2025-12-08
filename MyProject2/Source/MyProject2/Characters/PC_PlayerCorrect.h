// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "PC_PlayerCorrect.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API APC_PlayerCorrect : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
};
