// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}


void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}



float ATank::TakeDamage
(
	float DamageAmount,
	struct FDamageEvent const & DamageEvent,
	class AController * EventInstigator,
	AActor * DamageCauser
)
{
	int32 DamagePoints = FMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);
	
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		CurrentHealth = 0;
		//tell whoever is bound to the OnTankDied delegate, that the tank is dead
		OnTankDied.Broadcast();
	}

	return DamageToApply;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}
