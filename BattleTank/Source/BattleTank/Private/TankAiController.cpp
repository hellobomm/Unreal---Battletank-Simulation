// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAiController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"


void ATankAiController::BeginPlay()
{
	Super::BeginPlay(); //call the default behaviour before we go on
	UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) return;
}


void ATankAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank&&ControlledTank)) return;

	
	//Move towards the player   (generates a request to move along a vector towards the player. 
								//Then the RequestDirectMove() for the controlled tank is called which can be overidden)
	MoveToActor(PlayerTank, AcceptanceRadius); //TODO check radius is in cm
		
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) return;

	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	AimingComponent->fire();
}

void ATankAiController::SetPawn(APawn * InPawn) 
{
	Super::SetPawn(InPawn);

	//bind to the delegate that broadcasts the message that the Tank has died
	if (InPawn)
	{
		auto PossesedTank = Cast<ATank>(InPawn);
		if (!ensure(PossesedTank)) { return; }
		
		//TODO Subscribe our local method to the tank's death event
		PossesedTank->OnTankDied.AddUniqueDynamic(this, &ATankAiController::OnPossessedTankDeath);
	}
}

void ATankAiController::OnPossessedTankDeath(void)
{
	UE_LOG(LogTemp,Warning,TEXT("Tank %s  died"),*(GetPawn()->GetName()) )
}
