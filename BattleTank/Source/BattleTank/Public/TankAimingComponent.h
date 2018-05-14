// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"



//Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};



//Forward Declaration 
class UTankBarrel; //   - instead of using #include "TankBarrel.h"
class UTankTurret;


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Called from AIController and PlayerController
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "SetUp")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	//U means it was inherrited ultimately from a UObject. The Barrel is a StaticMeshcomponent (see Tank Blueprint)
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
		
	//called from AimAt
	void MoveBarrelToward(FVector AimDirection);

	//TODO remove once firing is moved to aiming component
	UPROPERTY(EditDefaultsOnly, Category = "Firing")   //EditAnyWhere means, value can be edited in every instance and set to a different value
		float LaunchSpeed = 4000;


protected:
	//define the Status of the TankAimingComponent
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Aiming;
};
