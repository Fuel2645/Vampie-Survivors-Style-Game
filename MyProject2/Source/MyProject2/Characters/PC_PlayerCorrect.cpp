// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PC_PlayerCorrect.h"

void APC_PlayerCorrect::BeginPlay()
{
	APC_PlayerCorrect::bShowMouseCursor = true;
	APC_PlayerCorrect::CurrentMouseCursor = EMouseCursor::Crosshairs;
}
