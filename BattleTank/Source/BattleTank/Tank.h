// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category= "SetUp")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "SetUp")
	int32 CurrentHealth=StartingHealth;  //ui!!

public:
	//will be called when Actor is hit (if another actor calls ApplyRadialDamage)
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

};
