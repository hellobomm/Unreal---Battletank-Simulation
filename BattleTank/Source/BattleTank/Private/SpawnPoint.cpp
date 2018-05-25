// dont you touch this - this is Alex stuff

#include "SpawnPoint.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


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

	//ok watch out now. We spawn the actor deferred that means, its Construction Script of Blueprints and
	//more importantly for us, its BeginPlay will NOT run! 
	auto NewActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, GetComponentTransform());
	if (!NewActor) return;

	//now we attach to the SpawnPoint
	NewActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform); //we have already set the transformation so just keep it
	
	//Now we can finish the spawning. Only NOW the BeginPlay of the spawned Actor will run. Ok because we are now attached and the spawned actor
	//will find the Tank they are ultimately now attached.
	UGameplayStatics::FinishSpawningActor(NewActor, GetComponentTransform());
}


// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

