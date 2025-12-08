// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyProject2/Interfaces/XP_Interface.h"
#include "ShardTypes.h"
#include "Components/SphereComponent.h"
#include "XPShard.generated.h"




UCLASS()
class MYPROJECT2_API AXPShard : public AActor, public IXP_Interface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXPShard();

private:
	UStaticMeshComponent* shardMesh;

	void move();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void XPShardMove() override;


	void Initalise(ShardTypes givenType);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	uint16 XPGainAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shard Type")
	ShardTypes m_ShardType;

	float m_MoveSpeed = 5.f;

};
