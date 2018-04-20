// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	ATank* GetControlledTank()const;
	
	virtual void BeginPlay() override;  //virtual function in the parent (Actor). 
										//A virtual function may be overwritten
						  
	virtual void Tick(float DeltaTime) override;	 // Called every frame


private:

	void AimTowardsCrosshair(); //start the Tank moving the barrel so that a shot would hit	
								//where the crosshair intersects the world
	
	bool GetSightRayHitLocation(FVector &HitLocation) const; //const means it is not allowed to change any variable of the class
										//true means "hit"

};
