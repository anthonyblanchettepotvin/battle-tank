// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "TankBarrelComponent.h"
#include "Projectile.h"
#include "Tank.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;

	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
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
	if (!Barrel || !Projectile || !IsReloaded()) { return; }

	AProjectile* NewProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, Barrel->GetSocketLocation(FName("Muzzle")), Barrel->GetSocketRotation(FName("Muzzle")));
	NewProjectile->Launch(InitialProjectileSpeed);

	LastFireTime = FPlatformTime::Seconds();
}

void ATank::AimAt(FVector Location)
{
	if (!AimingComponent) { return; }

	AimingComponent->AimAt(Location, InitialProjectileSpeed);
}

void ATank::SetBarrelComponentReference(UTankBarrelComponent* Value)
{
	AimingComponent->SetBarrelComponentReference(Value);

	Barrel = Value;
}

void ATank::SetTurretComponentReference(UTankTurretComponent* Value)
{
	AimingComponent->SetTurretComponentReference(Value);
}

bool ATank::IsReloaded() const
{
	return (FPlatformTime::Seconds() - LastFireTime) > ReloadSpeed;
}
