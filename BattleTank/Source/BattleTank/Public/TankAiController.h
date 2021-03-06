// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAiController.generated.h"
//Depends on movement component via pathfinding system


/**
 * 
 */


UCLASS()
class BATTLETANK_API ATankAiController : public AAIController
{
	GENERATED_BODY()

protected:
	//How close can the AI Tank get to the player
	UPROPERTY(EditDefaultsOnly, Category="SetUp")  //can not be changed in individual AIController of each tank
		float AcceptanceRadius = 8000.f;

public:
	virtual void Tick(float DeltaTime) override;

private:
	void BeginPlay() override; //virtual function in the parent (Actor). A virtual function may be overwritten					   
};
