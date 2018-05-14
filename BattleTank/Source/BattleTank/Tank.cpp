// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Starting Timer
	LastReloadTime = FPlatformTime::Seconds();
}


void ATank::BeginPlay()
{
	Super::BeginPlay(); //Needed for BP BeginPlay to run!
}


void ATank::fire()
{
	//if (!ensure(Barrel))return;
	//bool isReloaded = (FPlatformTime::Seconds() - LastReloadTime) > ReloadSeconds;
	//
	//if (isReloaded)
	//{
	//	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
	//		Barrel->GetSocketLocation(FName("Projectile")), //Socket was put on Barrel in tank_fbx_Barrel, 
	//		Barrel->GetSocketRotation(FName("Projectile")));

	//	if (!Projectile)
	//	{
	//		UE_LOG(LogTemp,Error, TEXT("Spawn of Projectile failed. Check if the Projectile Blueprint in TankBlueprint is set"))
	//		GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
	//	}
	////	else Projectile->LaunchProjectile(LaunchSpeed);  TODO this will end up in Aiming Component
	//	LastReloadTime = FPlatformTime::Seconds();
	//}
}
