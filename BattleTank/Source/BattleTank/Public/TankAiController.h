// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAiController.generated.h"
//Depends on movement component via pathfinding system

class UTankAimingComponent;

/**
 * 
 */


UCLASS()
class BATTLETANK_API ATankAiController : public AAIController
{
	GENERATED_BODY()


public:
	virtual void Tick(float DeltaTime) override;

	//How close can the AI Tank get to the player
	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 3000.f;

private:
	void BeginPlay() override; //virtual function in the parent (Actor). A virtual function may be overwritten					   
};
