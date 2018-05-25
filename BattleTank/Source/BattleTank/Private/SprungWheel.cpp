// dont you touch this - this is Alex stuff

#include "SprungWheel.h"



// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelConstraint"));
	SetRootComponent(MassWheelConstraint);
	
	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetupAttachment(MassWheelConstraint);  //better version than in projectile
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
	MassWheelConstraint->SetConstrainedComponents(TankBodyPrimitive, NAME_None, Wheel, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

