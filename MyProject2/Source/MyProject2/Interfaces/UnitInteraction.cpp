// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/UnitInteraction.h"

// Add default functionality here for any IUnitInteraction functions that are not pure virtual.

void IUnitInteraction::Damage(float inDamage)
{
}

void IUnitInteraction::PoisonDamageStart(float inDamage, float TimeBetween)
{
}

void IUnitInteraction::PoisonDamageEnd()
{
}

void IUnitInteraction::FireDamageStart(float inDamage, float TimeBetween)
{
}

void IUnitInteraction::FireDamageEnd()
{
}

void IUnitInteraction::SlowStart(float Duration, float slowPercentage)
{
}

void IUnitInteraction::SlowEnd()
{
}

void IUnitInteraction::StunStart(float Duration)
{
}

void IUnitInteraction::StunEnd()
{
}
