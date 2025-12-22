// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PC_PlayerCorrect.h"

void APC_PlayerCorrect::BeginPlay()
{
	APC_PlayerCorrect::bShowMouseCursor = true;
	APC_PlayerCorrect::CurrentMouseCursor = EMouseCursor::Crosshairs;
}

void APC_PlayerCorrect::XPChange(int xpChangeAmmount)
{
	XPAmount += xpChangeAmmount;

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("xp gain ammount: %i"), xpChangeAmmount));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("new xp ammount: %i"), XPAmount));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, "Testing");
}
