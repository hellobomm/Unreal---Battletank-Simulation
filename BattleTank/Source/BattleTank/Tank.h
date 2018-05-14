// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "Tank.generated.h"



//Forward Declarations
class UTankBarrel; 
class AProjectile;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable)
		void fire();

private:
	// Sets default values for this pawn's properties
	ATank();

	void BeginPlay();
	
	UPROPERTY(EditDefaultsOnly, Category = "SetUp")
		TSubclassOf<AProjectile> ProjectileBlueprint; //makes the "ProjectileBlueprint" available to the TankBlueprint

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		double ReloadSeconds = 3;

	//Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;  //TODO Remove

	double LastReloadTime = 0.0;

};
