// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "Tank.generated.h"



//Forward Declarations
class UTankBarrel; 
class UTankTurret;
class UTankAimingComponent; 
class AProjectile;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()


public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
		void fire();

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();
	
	UPROPERTY(EditDefaultsOnly, Category = "SetUp")
		TSubclassOf<AProjectile> ProjectileBlueprint; //makes the "ProjectileBlueprint" available to the TankBlueprint
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")   //EditAnyWhere means, value can be edited in every instance and set to a different value
		float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		double ReloadSeconds = 3;

	//Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;  //TODO Remove

	double LastReloadTime = 0.0;

};
