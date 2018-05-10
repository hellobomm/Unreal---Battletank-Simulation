// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack; 
/**
 * Responsible to drive the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent   //we used NavMovementComponent as it works with Pathfinding
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void IntendMoveForward(float Throw);
	UFUNCTION(BlueprintCallable)
		void IntendTurnRight(float Throw);

	//TODO check best protection for this method
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;


	UFUNCTION(BlueprintCallable, Category = SetUp)
	void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	
	
private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
	
};
