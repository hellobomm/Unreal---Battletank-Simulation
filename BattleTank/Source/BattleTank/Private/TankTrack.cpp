// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	
	auto ForceApplied = GetForwardVector()*Throttle*TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());   
	//Owner ist Tank_BP, RootCompomemt ist Tank (StaticMesh)
	//Casting because on PrimitiveComponents, forces can be applied
	//The StaticMeshComponent is inherited from a MeshComponent which is inherited from a PrimitiveComponent
	//see class hirarchy

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

	//auto Time = GetWorld()->GetTimeSeconds();
	auto TrackName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s: force at: %s"), *TrackName, *(ForceApplied.ToString()))


}

