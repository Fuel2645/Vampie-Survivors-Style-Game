// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyController.generated.h"




UCLASS()
class MYPROJECT2_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:

protected:
	virtual void BeginPlay() override;
	
private:
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	void Rotation();
	void Movement();
	void playerDistanceCheck();
	FTimerHandle m_RotationTimer;
	FTimerHandle m_movementCheckTimer;

	APawn* playerReference;

	virtual void UpdateControlRotation(float DeltaTime, bool bUpdatePawn) override;



};
