// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Engine/World.h"
#include "TimerManager.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//No need to protect pointers

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(true);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	//Attach means it moves with the owner
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false; //makes projectile not shoot off when spawned

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement Component"));
	ProjectileMovement->bAutoActivate = false; //makes projectile not shoot off when spawned

	
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	//Register OnHit to be called when "this" component is hit
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}



//gets called every frame if there is contact
void AProjectile::OnHit(UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse();

	//we plan do destroy the CollisionMesh which is the current RootComponent. So first we set the new RootComponent. If we delete the RootObject Unreal does not crash but this is cleaner
	SetRootComponent(ImpactBlast); 
	//and then we can destroy the CollisionMesh. It also contains the Texture of the projectile so it becomes invisible
	CollisionMesh->DestroyComponent();

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::OnTimerExpire, DestroyDelay);
}

void AProjectile::LaunchProjectile(float speed)
{
	if (!ensure(ProjectileMovement))return;
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector*speed);
	ProjectileMovement->Activate(true); //only NOW it moves
}

//our DelegateMethod
void AProjectile::OnTimerExpire()
{
	Destroy();
}