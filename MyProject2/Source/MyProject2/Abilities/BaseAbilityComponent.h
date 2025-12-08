// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseAbilityComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT2_API UBaseAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseAbilityComponent();
	UBaseAbilityComponent(float GivenAbilityDuration);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	FVector2d GetPointInCirlce(float Radius);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	virtual void Activation();
	UFUNCTION(BlueprintCallable)
	virtual void StopAbility();

	UPROPERTY(BlueprintReadWrite)
	FTimerHandle DurationTimer;
	FTimerHandle CooldownTimer;

	UPROPERTY(BlueprintReadWrite)
	float AbilityDuration;
	float AbilityCooldownDuration;

	bool AbilityCoolDown =false;

	void SetAbilityReady() { AbilityCoolDown = false; };

private:
	
};
