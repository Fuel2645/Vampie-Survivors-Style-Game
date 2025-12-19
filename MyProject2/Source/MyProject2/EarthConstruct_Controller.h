// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"
#include "Characters/Enemy_Base.h"
#include "EarthConstruct_Controller.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API AEarthConstruct_Controller : public AAIController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
private:
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
	virtual void UpdateControlRotation(float DeltaTime, bool bUpdatePawn) override;
	AActor* GetClosestActor();

	void Movement();
	APawn* enemyReference;
	FTimerHandle AICheckTimer;

};
