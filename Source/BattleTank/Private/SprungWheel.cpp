// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "SprungWheel.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/EngineTypes.h"
#include "Engine/StaticMesh.h"
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
	PhysicsConstraintComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 150.0f));
	SetRootComponent(PhysicsConstraintComponent);

	WheelMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("WheelMeshComponent"));
	WheelMeshComponent->SetMobility(EComponentMobility::Movable);
	WheelMeshComponent->SetSimulatePhysics(true);
	WheelMeshComponent->SetupAttachment(RootComponent);

	MassMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("MassMeshComponent"));
	MassMeshComponent->SetMobility(EComponentMobility::Movable);
	MassMeshComponent->SetSimulatePhysics(true);
	MassMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 300.0f));
	MassMeshComponent->SetupAttachment(RootComponent);

	FConstrainComponentPropName ComponentName1;
	ComponentName1.ComponentName = FName(*WheelMeshComponent->GetName());
	PhysicsConstraintComponent->ComponentName1 = ComponentName1;
	FConstrainComponentPropName ComponentName2;
	ComponentName2.ComponentName = FName(*MassMeshComponent->GetName());
	PhysicsConstraintComponent->ComponentName2 = ComponentName2;
}

void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
}

void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
