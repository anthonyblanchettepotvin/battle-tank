// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "SprungWheel.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

ASprungWheel::ASprungWheel()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = ETickingGroup::TG_PostPhysics;
	
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

	AxleMesh = CreateDefaultSubobject<USphereComponent>(FName("AxleMesh"));
	AxleMesh->SetMobility(EComponentMobility::Movable);
	AxleMesh->SetSimulatePhysics(true);
	AxleMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	AxleMesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	AxleMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Overlap);
	AxleMesh->SetupAttachment(RootComponent);

	AxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleConstraint"));
	AxleConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	AxleConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	AxleConstraint->SetupAttachment(AxleMesh);

	WheelMesh = CreateDefaultSubobject<USphereComponent>(FName("WheelMesh"));
	WheelMesh->SetMobility(EComponentMobility::Movable);
	WheelMesh->SetSimulatePhysics(true);
	WheelMesh->SetCollisionProfileName(FName("PhysicsActor"));
	WheelMesh->SetNotifyRigidBodyCollision(true);
	WheelMesh->SetupAttachment(AxleMesh);

	RollingDirection = CreateDefaultSubobject<UArrowComponent>(FName("RollingDirection"));
	RollingDirection->SetupAttachment(RootComponent);

	WheelMesh->OnComponentHit.AddDynamic(this, &ASprungWheel::OnWheelMeshComponentHit);
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

	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		TotalDrivingForce = 0.0f;
	}
}

void ASprungWheel::AddDrivingForce(float DrivingForce)
{
	TotalDrivingForce += DrivingForce;
}

void ASprungWheel::ApplyDrivingForce()
{
	WheelMesh->AddForce(RollingDirection->GetForwardVector() * TotalDrivingForce);
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

void ASprungWheel::OnWheelMeshComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplyDrivingForce();
}
