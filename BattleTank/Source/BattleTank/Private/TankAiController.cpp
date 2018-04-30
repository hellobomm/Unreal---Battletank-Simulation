// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAiController.h"
#include "Tank.h"




void ATankAiController::BeginPlay()
{
	Super::BeginPlay(); //call the default behaviour before we go on
}


void ATankAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank)
	{
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->fire();
	}
}
