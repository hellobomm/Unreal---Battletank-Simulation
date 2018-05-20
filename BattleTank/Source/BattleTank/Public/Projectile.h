// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Runtime\Engine\Classes\Particles\ParticleSystemComponent.h"
#include "Projectile.generated.h"


UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UProjectileMovementComponent* ProjectileMovement = nullptr;
	UStaticMeshComponent* CollisionMesh = nullptr;
	UParticleSystemComponent* LaunchBlast = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//called by the tank
	void LaunchProjectile(float speed);

	
	
};
