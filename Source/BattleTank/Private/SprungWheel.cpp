// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "SprungWheel.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "DrawDebugHelpers.h"

ASprungWheel::ASprungWheel()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(Root);

	SpringConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("SpringConstraint"));
	SpringConstraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Free, 0.0f);
	SpringConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	SpringConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	SpringConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	SpringConstraint->SetLinearPositionDrive(false, false, true);
	SpringConstraint->SetLinearVelocityDrive(false, false, true);
	SpringConstraint->SetLinearDriveParams(100.0f, 10.0f, 0.0f);
	SpringConstraint->SetupAttachment(RootComponent);

	AxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleConstraint"));
	AxleConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	AxleConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	AxleConstraint->SetupAttachment(RootComponent);

	AxleMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("AxleMesh"));
	AxleMesh->SetMobility(EComponentMobility::Movable);
	AxleMesh->SetSimulatePhysics(true);
	AxleMesh->SetupAttachment(RootComponent);

	WheelMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("WheelMesh"));
	WheelMesh->SetMobility(EComponentMobility::Movable);
	WheelMesh->SetSimulatePhysics(true);
	WheelMesh->SetupAttachment(RootComponent);

	RollingDirection = CreateDefaultSubobject<UArrowComponent>(FName("RollingDirection"));
	RollingDirection->SetupAttachment(RootComponent);
}

void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	ConstrainToParentActorRoot();
	AxleConstraint->SetConstrainedComponents(
		AxleMesh,
		NAME_None,
		WheelMesh,
		NAME_None
	);
}

void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	WheelMesh->AddForce(RollingDirection->GetForwardVector() * ForceMagnitude);
}

void ASprungWheel::ConstrainToParentActorRoot()
{
	if (GetAttachParentActor())
	{
		UPrimitiveComponent* ParentActorRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());

		if (ParentActorRoot) {
			SpringConstraint->SetConstrainedComponents(
				ParentActorRoot,
				NAME_None,
				AxleMesh,
				NAME_None
			);
		}
	}
}
