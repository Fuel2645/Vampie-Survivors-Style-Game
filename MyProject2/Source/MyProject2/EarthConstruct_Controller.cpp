// Fill out your copyright notice in the Description page of Project Settings.


#include "EarthConstruct_Controller.h"

void AEarthConstruct_Controller::BeginPlay()
{
	Super::BeginPlay(); 

	FTimerHandle pauseBro;
	GetWorld()->GetTimerManager().SetTimer
	(
		pauseBro,
		this,
		&AEarthConstruct_Controller::Movement,
		0.1f,
		false
	);
}

void AEarthConstruct_Controller::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (Result.Code == EPathFollowingResult::Success)
	{
		if (!AICheckTimer.IsValid())
			GetWorld()->GetTimerManager().SetTimer(AICheckTimer, this, &AEarthConstruct_Controller::Movement, 0.5f, true);
	}
	else if (Result.Code == EPathFollowingResult::Aborted)
	{
		if (!AICheckTimer.IsValid())
			GetWorld()->GetTimerManager().SetTimer(AICheckTimer, this, &AEarthConstruct_Controller::Movement, 0.5f, true);
	}
	else if (Result.Code == EPathFollowingResult::Invalid)
	{
		if (!AICheckTimer.IsValid())
			GetWorld()->GetTimerManager().SetTimer(AICheckTimer, this, &AEarthConstruct_Controller::Movement, 0.5f, true);
	}
}

void AEarthConstruct_Controller::UpdateControlRotation(float DeltaTime, bool bUpdatePawn)
{
	Super::UpdateControlRotation(DeltaTime, bUpdatePawn);

	FRotator rotation = GetControlRotation();
	rotation.Pitch = 0;
	rotation.Roll = 0;
	SetControlRotation(rotation);
}

AActor* AEarthConstruct_Controller::GetClosestActor()
{
	float closestDistance = 0.0f;
	AActor* closestActor = this->GetPawn();
	TArray<AActor*> foundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy_Base::StaticClass(), foundActors);

	if (foundActors.Num() > 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(AICheckTimer);
		for (AActor* curActor : foundActors)
		{
			if (FVector::DistSquared(curActor->GetActorLocation(), this->GetPawn()->GetActorLocation()) < closestDistance || closestDistance == 0)
			{
				closestDistance = FVector::DistSquared(curActor->GetActorLocation(), this->GetPawn()->GetActorLocation());
				closestActor = curActor;
			}
		}
	}
	else
	{
		if(!AICheckTimer.IsValid())
			GetWorld()->GetTimerManager().SetTimer(AICheckTimer, this, &AEarthConstruct_Controller::Movement, 0.5f, true);
	}
	if (IsValid(closestActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, "Valid");
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Distance, %f"),closestDistance));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Invalid");
	}
		


	return closestActor;

}

void AEarthConstruct_Controller::Movement()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Movement");
	MoveToActor(GetClosestActor(), 10.0f, false);
}
