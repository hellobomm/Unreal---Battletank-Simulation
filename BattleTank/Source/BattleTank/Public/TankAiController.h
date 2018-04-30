// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAiController.generated.h"

/**
 * 
 */
 //Forward Declarations
class ATank; 


UCLASS()
class BATTLETANK_API ATankAiController : public AAIController
{
	GENERATED_BODY()


public:
	virtual void Tick(float DeltaTime) override;

private:
	void BeginPlay() override; //virtual function in the parent (Actor). A virtual function may be overwritten
							   

};
