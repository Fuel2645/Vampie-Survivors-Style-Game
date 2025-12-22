// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "Abilities/BaseAbilityComponent.h"
#include "Interfaces/PlayerInteractionInterface.h"
#include "Interfaces/XP_Interface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "InputMappingContext.h"
#include "Player_Background.generated.h"




UCLASS()
class MYPROJECT2_API APlayer_Background : public ACharacter, public IPlayerInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayer_Background();

	UPROPERTY(EditAnywhere, Category ="Input")
	UInputMappingContext* inputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* inputMove;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* inputDash;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* inputShoot;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* inputAbility1;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* inputAbility2;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* inputAbility3;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* inputAbility4;




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	virtual void Shoot(const FInputActionValue& Value);
	void Dash(const FInputActionValue& Value);
	virtual void Ability1(const FInputActionValue& Value);
	virtual void Ability2(const FInputActionValue& Value);
	virtual void Ability3(const FInputActionValue& Value);
	virtual void Ability4(const FInputActionValue& Value);

	virtual void Damage(float inDamage) override;
	virtual void IceSurfaceStart(float newFriction, float newBraking) override;
	virtual void IceSurfaceEnd() override;


	FVector GetMovementVector() { return m_MovementVector; };

	UStaticMeshComponent* Cube;
	UStaticMeshComponent* Gun;
	FTimerHandle ShootTimer;
	float ShootCooldown = 0.2f;

	void SetShootCheck() { ShootCheck = false; };


private:
	FVector m_MovementVector;

	UBaseAbilityComponent* Ability1Component;
	UBaseAbilityComponent* Ability2Component;
	UBaseAbilityComponent* Ability3Component;
	UBaseAbilityComponent* Ability4Component;



	UCameraComponent* Camera;

	APlayerController* PC;

	USphereComponent* xpSphereCollider;


	bool ShootCheck = false;

	float m_BaseFriction;
	float m_BaseBraking;

	UFUNCTION()
	void OnXPOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);



};
