// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay(); //call the default behaviour before we go on
	

	ATank* ControlledTank = GetControlledTank();
	
	if (!ControlledTank)
	{
		UE_LOG(LogTemp,Error,TEXT("PlayerController did not find the controlled Tank"))
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("The player-controlled Tank has the name: %s"), *(ControlledTank->GetName()))
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())return;

	FVector HitLocation; //Out Parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLoclacton: %s"), *HitLocation.ToString())
		//TODO Tell controlled tank to point at this tank
	}
	else
	{

	}

	
}

//Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLoc) const
{
	HitLoc = FVector(1.f, 2.f, 3.f);
	return true;
}


ATank* ATankPlayerController::GetControlledTank()const
{
	return Cast<ATank>(GetPawn());
}

