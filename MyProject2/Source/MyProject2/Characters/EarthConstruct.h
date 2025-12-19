// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EarthConstruct_Controller.h"
#include "EarthConstruct.generated.h"


UCLASS()
class MYPROJECT2_API AEarthConstruct : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEarthConstruct();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	AAIController* m_Controller;

	UStaticMeshComponent* Cube;
	UStaticMeshComponent* Gun;

	float m_HP = 100.f;
};
