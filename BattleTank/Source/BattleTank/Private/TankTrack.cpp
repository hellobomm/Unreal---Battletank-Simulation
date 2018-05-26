// Fill out your copyright notice in the Description page of Project Settings.



#include "TankTrack.h"
#include "Engine/World.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"
#include "Components/SceneComponent.h"



UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}


TArray<ASprungWheel*> UTankTrack::GetWheels() const  //const also here if it is in the header
{
	TArray<ASprungWheel*> ResultArray; //now let's populate it

	
	//first get the spawn points. These are child components of the Track
	TArray<USceneComponent*> children;
	GetChildrenComponents(true, children); //true means we want all decendants, not only the children
	
	//now iterate through the SpawnPoints
	for (USceneComponent* child : children)
	{
		auto SpawnPointChild = Cast<USpawnPoint>(child);
		if (!SpawnPointChild) continue;

		//aaand we find the Sprung wheel
		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel)continue;

		ResultArray.Add(SprungWheel);
	}
	return ResultArray;
}



void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle,-1.f,1.f);
	//Drive the Track
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied =	CurrentThrottle*TrackMaxDrivingForce;
	
	//get the TArray
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();

	for (ASprungWheel* Wheel : Wheels) //and apply Force to each wheel
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
	//auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//Owner ist Tank_BP, RootCompomemt ist Tank (StaticMesh)
	//Casting because on PrimitiveComponents, forces can be applied
	//The StaticMeshComponent is inherited from a MeshComponent which is inherited from a PrimitiveComponent
	//see class hirarchy

	//TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

	//auto Time = GetWorld()->GetTimeSeconds();
	/*auto TrackName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s: force at: %s"), *TrackName, *(ForceApplied.ToString()))*/
}

