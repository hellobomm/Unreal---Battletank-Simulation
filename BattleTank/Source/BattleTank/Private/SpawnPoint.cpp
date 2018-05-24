// dont you touch this - this is Alex stuff

#include "SpawnPoint.h"
#include "Engine/World.h"


// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	//
	auto NewActor = GetWorld()->SpawnActor<AActor>(SpawnClass);
	if (!NewActor) return;
	NewActor->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
}


// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

