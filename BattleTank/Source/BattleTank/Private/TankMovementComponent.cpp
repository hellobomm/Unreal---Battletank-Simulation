// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"




void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}


void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack&&RightTrack))return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack&&RightTrack))return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	//this method is called by TankAiController (which contols the AiTank) indirectly when calling MoveToActor() 
	//and we are intercepting it to use this for the movement of the AiTank
	//no Super call necessary as we are completely overwrighting the existing game engine method
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	//one when parallel, zero when perpendicular
	
	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	//zero when parallel, one when perpendicular

	//move fast when same direction. stop when perpendicular
	IntendMoveForward(ForwardThrow);

	//rotate, when Forward and Intention are not facing in same direction
	IntendTurnRight(RightThrow);
}
