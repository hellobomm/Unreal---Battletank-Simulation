// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//No need to protect pointers
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

	//Starting Timer
	LastReloadTime = FPlatformTime::Seconds();

}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret * TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// as the name says
void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::fire()
{
	//bool isReloaded = (FPlatformTime::Seconds() - LastReloadTime) > ReloadSeconds;
	//
	//if (Barrel&&isReloaded)
	//{
	//	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
	//		Barrel->GetSocketLocation(FName("Projectile")), //Socket was put on Barrel in tank_fbx_Barrel, 
	//		Barrel->GetSocketRotation(FName("Projectile")));
	//	Projectile->LaunchProjectile(LaunchSpeed);
	//	LastReloadTime = FPlatformTime::Seconds();
	//}
}
