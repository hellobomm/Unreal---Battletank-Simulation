// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


//Forward Declaration 
class UTankBarrel; //   - instead of using #include "TankBarrel.h"
class UTankTurret;


UCLASS(meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	void SetTurretReference(UTankTurret* TurretToSet);

public:	
	// Called from Tank
	void AimAt(FVector HitLocation, float LaunchSpeed);


private:
	//U means it was inherrited ultimately from a UObject. The Barrel is a StaticMeshcomponent (see Tank Blueprint)
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
		
	//called from AimAt
	void MoveBarrelToward(FVector AimDirection);
};
