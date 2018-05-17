// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"



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


void UTankTrack::OnHit(UPrimitiveComponent* HitComponent,
						AActor* OtherActor,
						UPrimitiveComponent* OtherComponent,
						FVector NormalImpulse,
						const FHitResult& Hit)
{
	UE_LOG(LogTemp,Warning,TEXT("%s   hit"), *GetName())


}




void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunktion)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunktion);

	//calculate slippage speed
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetOwner()->GetVelocity());

	//UE_LOG(LogTemp,Warning,TEXT("%f"),SlippageSpeed)

	//work out the required acceleration this frame to correct
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	//calculate and apply sideways for F=mxa
	auto TankRoot = Cast < UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankRoot->GetMass()*CorrectionAcceleration / 2; //two tracks
	TankRoot->AddForce(CorrectionForce);
}




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
	/*auto TrackName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s: force at: %s"), *TrackName, *(ForceApplied.ToString()))*/

}

