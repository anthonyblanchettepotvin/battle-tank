// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "SprungWheel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

ASprungWheel::ASprungWheel()
{
	PrimaryActorTick.bCanEverTick = false;

	PhysicsConstraintComponent = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("PhysicsConstraintComponent"));
	PhysicsConstraintComponent->SetLinearZLimit(ELinearConstraintMotion::LCM_Free, 0.0f);
	PhysicsConstraintComponent->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	PhysicsConstraintComponent->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	PhysicsConstraintComponent->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	PhysicsConstraintComponent->SetLinearPositionDrive(false, false, true);
	PhysicsConstraintComponent->SetLinearVelocityDrive(false, false, true);
	PhysicsConstraintComponent->SetLinearDriveParams(100.0f, 10.0f, 0.0f);
	SetRootComponent(PhysicsConstraintComponent);

	WheelMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("WheelMeshComponent"));
	WheelMeshComponent->SetMobility(EComponentMobility::Movable);
	WheelMeshComponent->SetSimulatePhysics(true);
	WheelMeshComponent->SetupAttachment(RootComponent);
}

void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	ConstrainToParentActorRoot();
}

void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASprungWheel::ConstrainToParentActorRoot()
{
	if (GetAttachParentActor())
	{
		UPrimitiveComponent* ParentActorRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());

		if (ParentActorRoot) {
			PhysicsConstraintComponent->SetConstrainedComponents(
				WheelMeshComponent,
				NAME_None,
				ParentActorRoot,
				NAME_None
			);
		}
	}
}
