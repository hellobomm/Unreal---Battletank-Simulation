// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"


//class ASprungWheel;  forward declarated down below!


/**
 * TankTrack is used to set maximum driving force and to apply forces to the tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public: 


	UFUNCTION(BlueprintCallable, Category = Input)
		void SetThrottle(float Throttle);
	
	//MaxForce per track in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 32000000.0f;


private:
	UTankTrack();

	//the keyword "class" forward declarates!!!
	//this function returns the pointers to the wheels
	TArray<class ASprungWheel*> GetWheels() const;

	void DriveTrack(float CurrentThrottle);
};


