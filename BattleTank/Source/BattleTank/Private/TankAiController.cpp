// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAiController.h"



void ATankAiController::BeginPlay()
{
	Super::BeginPlay(); //call the default behaviour before we go on


	ATank* ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("AIController did not find the controlled Tank"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("The AI-controlled Tank has the name: %s"), *(ControlledTank->GetName()))
	}
}


ATank * ATankAiController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
