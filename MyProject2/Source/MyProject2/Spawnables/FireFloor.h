// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "MyProject2/Interfaces/UnitInteraction.h"
#include "FireFloor.generated.h"

UCLASS()
class MYPROJECT2_API AFireFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UStaticMesh* floorMesh;
	UMaterialInterface* materialRef;
	USplineComponent* m_Spline;
	TArray<USplineMeshComponent*> m_SplinePoints;

	AActor* actorToFollow;

	int32 CurIndex;
	float m_Damage;
	float minPointSpacing = 30.f;
	FVector lastLocation;


	void pathLogic();
	void UpdatePath();
	void UpdateSplineMeshes();



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
