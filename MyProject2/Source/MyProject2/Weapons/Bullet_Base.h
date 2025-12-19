// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/UnitInteraction.h"
#include "Bullet_Base.generated.h"


UCLASS()
class MYPROJECT2_API ABullet_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet_Base();

protected:
	// Called when the game starts or when spawned
	
	float m_MovementSpeed = 10.f;
	float m_Damage = 10.f;
	
	TArray<AActor*> overlappingActors;

	virtual void BeginPlay() override;
	virtual void Movement();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetDamage() { return m_Damage; };
	float GetSpeed() { return m_MovementSpeed; };
	void SetDamage(float newDamage) { m_Damage = newDamage; };
	void SetSpeed(float newSpeed) { m_MovementSpeed = newSpeed; };
	UStaticMeshComponent* bulletMesh;
private:
	

	UFUNCTION()
	virtual void OnOverlapBegin(
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

	


	FTimerHandle m_MovementTimer;
};
