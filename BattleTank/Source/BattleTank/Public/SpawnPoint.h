// dont you touch this - this is Alex stuff

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnPoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnPoint();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AActor* GetSpawnedActor()const {return SpawnedActor;} //kakkoii!!!

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "SetUp")
		TSubclassOf<AActor> SpawnClass; //makes the "SpawnClass" be chosen in the Tankblueprint of which the SpawnPoint is a component
			
	UPROPERTY()  //needed so the garbage collector takes care of it
	AActor* SpawnedActor = nullptr;
};
