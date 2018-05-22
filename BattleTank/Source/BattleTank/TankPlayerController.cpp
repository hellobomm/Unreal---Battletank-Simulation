// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay(); //call the default behaviour before we go on

	UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) return;

	FoundAimingComponent(AimingComponent); //this triggers the blueprint event
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn())return;  //if not possessing. can easily be when dying
	UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) return;

	FVector HitLocation; //Out Parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		//Tell Aiming Component to point at this tank
		AimingComponent->AimAt(HitLocation);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("no hit"))
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

	//De-project the screen position of the crosshair to a world direction
	FVector	Lookdirektion;
	FVector CameraWorldLocation; //Cameraposition
	if (!GetLookDirection(ScreenLocation, Lookdirektion, CameraWorldLocation))
	{
		return false;
	}
	//Line-trace along that look direction, and see what we hit (up to max range)
	if (!GetLookVectorHitLocation(CameraWorldLocation, Lookdirektion, HitLoc))
	{
		return false;
	}
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector &CameraWorldLocation, FVector &Lookdirektion, FVector &HitLocation) const
{
	//Linetrace out to this distance in the LookDirection
	FHitResult ResultOfHit;
	if (!GetWorld()->LineTraceSingleByChannel(	ResultOfHit,
												CameraWorldLocation, //Ray Start
												CameraWorldLocation + LineTraceRange*Lookdirektion, //Ray End
												ECC_Camera))
	{
		return false;
	}

	
	HitLocation = ResultOfHit.Location;
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection, FVector& CameraWorldLocation) const
{
	return DeprojectScreenPositionToWorld(	ScreenLocation.X,
											ScreenLocation.Y,
											CameraWorldLocation,
											LookDirection);
}


void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	//bind to the delegate that broadcasts the message that the Tank has died
	if (InPawn)
	{
		auto PossesedTank = Cast<ATank>(InPawn);
		if (!ensure(PossesedTank)) { return; }

		//TODO Subscribe our local method to the tank's death event
		PossesedTank->OnTankDied.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}


void ATankPlayerController::OnPossessedTankDeath(void)
{
	UE_LOG(LogTemp, Warning, TEXT("Tank %s  died"), *(GetPawn()->GetName()))
	//let our ghost over above our dead tank
	StartSpectatingOnly();
}