// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAiController.h"
#include "Tank.h"




void ATankAiController::BeginPlay()
{
	Super::BeginPlay(); //call the default behaviour before we go on


	ATank* PlayerTank = GetPlayerTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("AIController did not find the Player Tank"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("The Player Tank has the name: %s"), *(PlayerTank->GetName()))
	}
}


void ATankAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
}

ATank * ATankAiController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


ATank * ATankAiController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn) { return nullptr;}
	else
	{
		return Cast<ATank>(PlayerPawn);
	}
}	