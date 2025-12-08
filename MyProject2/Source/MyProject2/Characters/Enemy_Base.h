// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "MyProject2/EnemyController.h"
#include "MyProject2/Characters/XPShard.h"
#include "MyProject2/Interfaces/UnitInteraction.h"
#include "MyProject2/ST_Enemy.h"
#include "Enemy_Base.generated.h"

UCLASS()
class MYPROJECT2_API AEnemy_Base : public ACharacter, public IUnitInteraction 
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Damage(float inDamage) override;
	void PoisonDamageStart(float inDamage, float TimeBetween) override;
	void PoisonDamage();
	void PoisonDamageEnd() override;
	void SlowStart(float Duration, float slowPercentage) override;
	void SlowEnd() override;
	void StunStart(float Duration) override;
	void StunEnd() override;
	void Initalise(FST_EnemyDataRow* data);

private:
	AAIController* m_Controller;

	UStaticMeshComponent* Cube;
	UStaticMeshComponent* Gun;

	float m_HP = 100.f;
	float poisonDamage;
	float baseMovementSpeed;
	bool isPoisoned = false;
	FTimerHandle poisonTimer;
	
	ShardTypes m_Shardtype;


	void DeathCheck();

};
