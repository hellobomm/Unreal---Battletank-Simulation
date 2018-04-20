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
		UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString())
		//TODO Tell controlled tank to point at this tank
	}
	else
	{

	}

	
}

//Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLoc) const
{
	//Find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	
	FVector2D ScreenLocation = FVector2D(	static_cast<float_t>(ViewportSizeX)*CrossHairXLocation,
											static_cast<float_t>(ViewportSizeY)*CrossHairYLocation);
	FVector	Lookdirektion;
	
	//De-project the screen position of the crosshair to a world direction
	//Line-trace along that look direction, and see what we hit (up to max range)
	if (GetLookDirection(ScreenLocation, Lookdirektion))
	{
		HitLoc = Lookdirektion;
	}
	
	
	HitLoc = Lookdirektion;
	return true;


}


ATank* ATankPlayerController::GetControlledTank()const
{
	return Cast<ATank>(GetPawn());
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; //Cameraposition
	return DeprojectScreenPositionToWorld(	ScreenLocation.X,
											ScreenLocation.Y,
											CameraWorldLocation,
											LookDirection);
}
