// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay(); //call the default behaviour before we go on
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"))

	ATank* ControlledTank = GetControlledTank();
	
	if (!ControlledTank)
	{
		UE_LOG(LogTemp,Error,TEXT("PlayerController did not find the controlled Tank"))
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("The first wonda Tank has the name: %s"), *(ControlledTank->GetName()))
	}
}


ATank* ATankPlayerController::GetControlledTank()const
{
	return Cast<ATank>(GetPawn());
}

