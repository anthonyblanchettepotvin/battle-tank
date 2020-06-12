// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "TimerManager.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(Root);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("ProjectileMesh"));
	ProjectileMesh->SetNotifyRigidBodyCollision(true);
	ProjectileMesh->SetupAttachment(RootComponent);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("LaunchBlast"));
	LaunchBlast->SetAutoActivate(false);
	LaunchBlast->SetupAttachment(RootComponent);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("ImpactBlast"));
	ImpactBlast->SetAutoActivate(false);
	ImpactBlast->SetupAttachment(RootComponent);

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("ExplosionForce"));
	ExplosionForce->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	ProjectileMovement->SetAutoActivate(false);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (ProjectileMesh)
	{
		ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::HandleCollisionMeshOnComponentHit);
	}
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::Launch(const float Speed)
{
	if (!ProjectileMovement) { return; }

	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();

	if (LaunchBlast)
	{
		LaunchBlast->Activate();
	}
}

void AProjectile::DestroyProjectile()
{
	Destroy();
}

void AProjectile::HandleCollisionMeshOnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ProjectileMesh)
	{
		ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ProjectileMesh->SetVisibility(false);
	}
	
	if (LaunchBlast && ImpactBlast)
	{
		LaunchBlast->Deactivate();
		ImpactBlast->Activate();
	}

	if (ExplosionForce)
	{
		ExplosionForce->FireImpulse();
		UGameplayStatics::ApplyRadialDamage(
			this,
			ProjectileDamage,
			Hit.ImpactPoint,
			ExplosionForce->Radius,
			UDamageType::StaticClass(),
			TArray<AActor*>(),
			this
		);
	}

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AProjectile::DestroyProjectile, 20.0f, false);
}
