// Fill out your copyright notice in the Description page of Project Settings.



#include "EnemyController.h"
#include "Navigation/PathFollowingComponent.h"



void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	

	playerReference = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	FTimerHandle pauseBro;
	GetWorld()->GetTimerManager().SetTimer
	(
		pauseBro,
		this,
		&AEnemyController::Movement,
		0.1f,
		false
	);

}

void AEnemyController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (Result.Code == EPathFollowingResult::Success)
	{
		Movement();
	}
	else if (Result.Code == EPathFollowingResult::Aborted)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, "Abortion");
	}
	else if (Result.Code == EPathFollowingResult::Invalid)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, "Invalid");
	}
}

void AEnemyController::Rotation()
{
	FVector Direction = playerReference->GetActorLocation() - this->GetPawn()->GetActorLocation();
	this->GetPawn()->SetActorRotation(FMath::RInterpTo(this->GetPawn()->GetActorRotation(), Direction.Rotation(), GetWorld()->GetDeltaSeconds(), 90.f));
	
}

void AEnemyController::Movement()
{
	MoveToActor(playerReference, 10.f, false);
}

void AEnemyController::UpdateControlRotation(float DeltaTime, bool bUpdatePawn)
{
	Super::UpdateControlRotation(DeltaTime, bUpdatePawn);

	FRotator rotation = GetControlRotation();
	rotation.Pitch = 0;
	rotation.Roll = 0;
	SetControlRotation(rotation);
}

