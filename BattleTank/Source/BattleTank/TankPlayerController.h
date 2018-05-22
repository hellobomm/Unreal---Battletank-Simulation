// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //must be the last include


//Forward Declarations
class UTankAimingComponent;

/**
 * Responsible for helping the player aim
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:
	virtual void BeginPlay() override;  //virtual function in the parent (Actor). 
										//A virtual function may be overwritten

	virtual void Tick(float DeltaTime) override;	 // Called every frame

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "SetUp") //this makro makes it possible that we don't need a definition of the
		void FoundAimingComponent(UTankAimingComponent* AimCompRef); //function. In fact the makro generates it before compilation (see generated file)
					
private:

	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection, FVector& CameraWorldLocation) const;
	
	virtual void SetPawn(APawn* InPawn) override; //gets called when the pawn is possesed
												  //the right moment to register (to bind) to our delegate for receiving broadcasts

	//if the possessed tank dies
	UFUNCTION()
		void OnPossessedTankDeath();

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation=0.5f;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation=0.3333f;
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;	//Range is 10km 

	void AimTowardsCrosshair(); //start the Tank moving the barrel so that a shot would hit	
								//where the crosshair intersects the world
	
	bool GetSightRayHitLocation(FVector &HitLocation) const; //const means it is not allowed to change any variable of the class
														     //true means "hit"

	bool GetLookVectorHitLocation(FVector &CameraWorldLocation, FVector &Lookdirektion, FVector &HitLocation) const;

};
