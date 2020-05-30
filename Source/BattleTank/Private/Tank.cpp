// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "TankBarrelComponent.h"
#include "Projectile.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::Fire()
{
	if (!Barrel || !Projectile) { return; }

	AProjectile* NewProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, Barrel->GetSocketLocation(FName("Muzzle")), Barrel->GetSocketRotation(FName("Muzzle")));
	NewProjectile->Launch(InitialProjectileSpeed);
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
