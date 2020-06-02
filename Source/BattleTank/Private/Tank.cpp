// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#include "Tank.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "TankBarrelComponent.h"
#include "TankMovementComponent.h"
#include "Projectile.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;

	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
	MovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("MovementComponent"));
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::Fire()
{
	UTankBarrelComponent* Barrel = AimingComponent->GetBarrelRef();

	if (!ensure(AimingComponent && Projectile && Barrel)) { return; }

	if (!IsReloaded()) { return; }

	AProjectile* NewProjectile = GetWorld()->SpawnActor<AProjectile>(
		Projectile,
		Barrel->GetSocketLocation(FName("Muzzle")),
		Barrel->GetSocketRotation(FName("Muzzle"))
	);

	NewProjectile->Launch(InitialProjectileSpeed);

	LastFireTime = FPlatformTime::Seconds();
}

bool ATank::IsReloaded() const
{
	return (FPlatformTime::Seconds() - LastFireTime) > ReloadSpeed;
}
