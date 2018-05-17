// Fill out your copyright notice in the Description page of Project Settings.



#include "TankTrack.h"
#include "Engine/World.h"



UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts or when spawned
void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	//Register OnHit to be called when "this" component is hit
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}


//gets called every frame if there is contact
void UTankTrack::OnHit(UPrimitiveComponent* HitComponent,
						AActor* OtherActor,
						UPrimitiveComponent* OtherComponent,
						FVector NormalImpulse,
						const FHitResult& Hit)
{
	//Drive the Track
	DriveTrack();

	//Apply a sideways Force
	ApplySideWaysForce();

	//Reset Throttle
	CurrentThrottle = 0.f;
}

void UTankTrack::ApplySideWaysForce()
{
	//calculate slippage speed
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetOwner()->GetVelocity());

	//UE_LOG(LogTemp,Warning,TEXT("%f"),SlippageSpeed)

	//work out the required acceleration this frame to correct
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	//calculate and apply sideways for F=mxa
	auto TankRoot = Cast < UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankRoot->GetMass()*CorrectionAcceleration / 2; //two tracks
	TankRoot->AddForce(CorrectionForce);
}



void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle,-1.f,1.f);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector()*CurrentThrottle*TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//Owner ist Tank_BP, RootCompomemt ist Tank (StaticMesh)
	//Casting because on PrimitiveComponents, forces can be applied
	//The StaticMeshComponent is inherited from a MeshComponent which is inherited from a PrimitiveComponent
	//see class hirarchy

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

	//auto Time = GetWorld()->GetTimeSeconds();
	/*auto TrackName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s: force at: %s"), *TrackName, *(ForceApplied.ToString()))*/
}

