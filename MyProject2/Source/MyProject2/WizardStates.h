// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WizardStates.generated.h"


UENUM()
enum class WizardStates : uint8
{
	QQQ = 0 UMETA(DisplayName = "QQQ"),  //3q
	QQW = 1 UMETA(DisplayName = "QQW"), //2q 1w
	QWW = 2 UMETA(DisplayName = "QWW"), //1q 2w
	QQE = 3 UMETA(DIsplayName = "QQE"), //2q 1e
	QEE = 4 UMETA(DIsplayName = "QEE"), //1q 2e
	EEE = 5 UMETA(DIsplayName = "EEE"), //3e
	EEW = 6 UMETA(DIsplayName = "EEW"), //2e 1w
	EWW = 7 UMETA(DIsplayName = "EWW"), //1e 2w
	WWW = 8 UMETA(DIsplayName = "WWW") //3w
};
