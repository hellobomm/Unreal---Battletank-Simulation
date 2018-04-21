// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:
	virtual void BeginPlay() override;  //virtual function in the parent (Actor). 
										//A virtual function may be overwritten

	virtual void Tick(float DeltaTime) override;	 // Called every frame


private:

	ATank* GetControlledTank()const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection, FVector& CameraWorldLocation) const;
	
	

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation=0.5f;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation=0.3333f;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;	//Range is 10km

	void AimTowardsCrosshair(); //start the Tank moving the barrel so that a shot would hit	
								//where the crosshair intersects the world
	
	bool GetSightRayHitLocation(FVector &HitLocation) const; //const means it is not allowed to change any variable of the class
										//true means "hit"

	bool GetLookVectorHitLocation(FVector &CameraWorldLocation, FVector &Lookdirektion, FVector &HitLocation) const;

};
