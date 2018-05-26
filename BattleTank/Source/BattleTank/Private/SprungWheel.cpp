// dont you touch this - this is Alex stuff

#include "SprungWheel.h"
#include "Components/PrimitiveComponent.h"



// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;  //that is important we maybe want to eliminate a force AFTER being hit
												  //the hit is detected during physics. So our tick must be after that.

	MassAxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassAxleConstraint"));
	SetRootComponent(MassAxleConstraint);
	
	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(MassAxleConstraint);

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
	AxleWheelConstraint->SetupAttachment(Axle);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);  //better version than in projectile
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	//if we have contact to the ground
	Wheel->SetNotifyRigidBodyCollision(true); //register
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);

	SetupConstraint();
}

void ASprungWheel::SetupConstraint()
{
	auto ParentTank = GetAttachParentActor();
	if (!ParentTank)return;
	UPrimitiveComponent* TankBodyPrimitive = Cast<UPrimitiveComponent>(ParentTank->GetRootComponent());
	if (!TankBodyPrimitive)return;

	MassAxleConstraint->SetConstrainedComponents(TankBodyPrimitive, NAME_None, Axle, NAME_None);
	AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}


void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	TotalForceMagnitudeThisFrame += ForceMagnitude;
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TickGroup == TG_PostPhysics) //juuust to be sure. We have set that already in the constructor
	{
		TotalForceMagnitudeThisFrame = 0; //we make sure that this is zero before the next frame
	}
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//apply the force not when we are flying
	ApplyForce();
}

void ASprungWheel::ApplyForce()
{
	Wheel->AddForce(Axle->GetForwardVector()*TotalForceMagnitudeThisFrame, NAME_None);
}