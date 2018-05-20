// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"  //has to be included. Forward Declaration not working if a method is called here
#include "TankTurret.h" //has to be included. Forward Declaration not working if a method is called here
#include "Projectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	//Starting Timer
	LastReloadTime = FPlatformTime::Seconds();
}



void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunktion)
{
	if (RoundsLeft <= 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}	
	else if ((FPlatformTime::Seconds() - LastReloadTime) < ReloadSeconds)
		{
			FiringState = EFiringState::Reloading;
			//UE_LOG(LogTemp, Warning, TEXT("reloading"))
		}
		else if (isBarrelMoving())
			{
				//UE_LOG(LogTemp, Warning, TEXT("aiming"))
				FiringState = EFiringState::Aiming;
			}
			else
			{
				//UE_LOG(LogTemp, Warning, TEXT("locked"))
				FiringState = EFiringState::Locked;
			}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel&&Turret))return;

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); //Socket was put on Barrel in tank_fbx_Barrel

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
															(	this,
																OutLaunchVelocity,
																StartLocation,
																HitLocation,
																LaunchSpeed,
																false,
																0,
																0,
																ESuggestProjVelocityTraceOption::DoNotTrace);
		
	if (bHaveAimSolution)
	{
		float LaunchFinalSpeed;
		OutLaunchVelocity.ToDirectionAndLength(AimDirection, LaunchFinalSpeed);

		auto TankName = GetOwner()->GetName();

	//	auto Time = GetWorld()->GetTimeSeconds();
	//	UE_LOG(LogTemp, Warning, TEXT("%f: Aim Solution found"), Time)
		MoveBarrelToward(AimDirection);
	}
	else
	{
	//	auto Time = GetWorld()->GetTimeSeconds();
	//	UE_LOG(LogTemp, Warning, TEXT("%f: no Solution found"), Time)
	}
	
}

void UTankAimingComponent::MoveBarrelToward(FVector AimDirection)
{
	//Work out difference between current barrel rotation and aimdirection
	if (!ensure(Barrel&&Turret))return;
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();  //struct which contains yaw pitch roll
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);

	//correction of rotation when we point directly back
	float Yaw = DeltaRotator.Yaw;
	if (Yaw > 180.0f)Yaw = Yaw-360.0f;
	if (Yaw < -180.0f)Yaw = Yaw + 360.0f;

	Turret->Rotate(Yaw);

}

bool UTankAimingComponent::isBarrelMoving()
{
	FVector CurrentForwardVector = Barrel->GetForwardVector();
	return !AimDirection.Equals(CurrentForwardVector,0.01f);
}

void UTankAimingComponent::fire()
{
	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
	{
		if (!ensure(Barrel&&ProjectileBlueprint))return;

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
						Barrel->GetSocketLocation(FName("Projectile")), //Socket was put on Barrel in tank_fbx_Barrel, 
						Barrel->GetSocketRotation(FName("Projectile")));

		if (!Projectile)
		{
			UE_LOG(LogTemp,Error, TEXT("Spawn of Projectile failed. Check if the Projectile Blueprint in TankBlueprint is set"))
			GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
		}
		else Projectile->LaunchProjectile(LaunchSpeed); 
		LastReloadTime = FPlatformTime::Seconds();
		RoundsLeft += -1;
		if (RoundsLeft <0)RoundsLeft = 0;
	}
}