// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "AIController.h"
#include "TankAiController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAiController : public AAIController
{
	GENERATED_BODY()
	
	ATank* GetControlledTank()const;
	
	void BeginPlay() override; //virtual function in the parent (Actor). A virtual function
							   //may be overwritten
};
