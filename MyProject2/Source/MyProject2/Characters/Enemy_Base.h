// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/HealthBar.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "EnemyController.h"
#include "Characters/XPShard.h"
#include "Interfaces/UnitInteraction.h"
#include "Interfaces/PLayerInteractionInterface.h"
#include "ST_Enemy.h"
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

	void Damage(float inDamage) override;
	void PoisonDamageStart(float inDamage, float TimeBetween) override;
	void PoisonDamage();
	void PoisonDamageEnd() override;
	void SlowStart(float Duration, float slowPercentage) override;
	void SlowEnd() override;
	void StunStart(float Duration) override;
	void StunEnd() override;
	void Initalise(FST_EnemyDataRow* data);
	const bool IsActive() { return isActive; }

private:
	AAIController* m_Controller;

	UStaticMeshComponent* Cube;
	UStaticMeshComponent* Gun;
	UStaticMeshComponent* BaseCircle;

	float m_HP = 100.f;
	float m_MaxHp;
	float m_Damage = 0;
	float poisonDamage;
	float baseMovementSpeed;

	bool isPoisoned = false;
	bool isActive = false;

	FTimerHandle damageTimer;
	FTimerHandle poisonTimer;
	
	ShardTypes m_Shardtype;

	UWidgetComponent* healthBar;

	TSubclassOf<UUserWidget> healthBarWidgetClass;

	void DeathCheck();
	void PlayerDamage();

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);


	UFUNCTION()
	virtual void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);
};
