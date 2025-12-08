// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAbilityComponent.h"

// Sets default values for this component's properties
UBaseAbilityComponent::UBaseAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

UBaseAbilityComponent::UBaseAbilityComponent(float GivenAbilityDuration)
{
	PrimaryComponentTick.bCanEverTick = false;
	AbilityDuration = GivenAbilityDuration;
}


// Called when the game starts
void UBaseAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

FVector2d UBaseAbilityComponent::GetPointInCirlce(float Radius)
{
	float Angle = FMath::RandRange(0.f, 2 * PI); //0-360 degree
	float Distance = Radius * FMath::Sqrt(FMath::FRand());

	return FVector2D(FMath::Cos(Angle)*Distance, FMath::Sin(Angle) * Distance);
}


// Called every frame
void UBaseAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBaseAbilityComponent::Activation()
{
}

void UBaseAbilityComponent::StopAbility()
{
}

