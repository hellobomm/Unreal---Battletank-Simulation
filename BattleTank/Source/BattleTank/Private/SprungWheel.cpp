// dont you touch this - this is Alex stuff

#include "SprungWheel.h"



// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	Wheel->AddForce(Axle->GetForwardVector()*ForceMagnitude, NAME_None);
}


// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

