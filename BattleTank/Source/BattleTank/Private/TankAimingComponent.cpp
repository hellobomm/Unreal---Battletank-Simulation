// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "TankBarrel.h"  //has to be included. Forward Declaration not working if a method is called here


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) return;

	//UE_LOG(LogTemp,Warning,TEXT("Firing at %f"), LaunchSpeed)
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); //Socket was put on Barrel in tank_fbx_Barrel

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
															(	this,
																OutLaunchVelocity,
																StartLocation,
																HitLocation,
																LaunchSpeed,
																ESuggestProjVelocityTraceOption::DoNotTrace);
		
	if (bHaveAimSolution)
	{

		FVector AimDirection;
		float LaunchFinalSpeed;
		OutLaunchVelocity.ToDirectionAndLength(AimDirection, LaunchFinalSpeed);

		auto TankName = GetOwner()->GetName();
		MoveBarrelToward(AimDirection);
	}
	else
	{
		//no solution
		UE_LOG(LogTemp, Warning, TEXT("no solution"))
	}
	
}

void UTankAimingComponent::MoveBarrelToward(FVector AimDirection)
{
	//Work out difference between current barrel rotation and aimdirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();  //struct which contains yaw pitch roll
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *DeltaRotator.ToString())

		Barrel->Elevate(5); //TODO remove magic number

}
