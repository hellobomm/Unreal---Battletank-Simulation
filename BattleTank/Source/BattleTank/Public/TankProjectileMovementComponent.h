// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TankProjectileMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankProjectileMovementComponent : public UProjectileMovementComponent
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	UTankProjectileMovementComponent();
	
	
};
