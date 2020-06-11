// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "TankBarrelComponent.h"
#include "TankTurretComponent.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();
	CurrentNumberOfAmmo = MaxNumberOfAmmo;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsOutOfAmmo())
	{
		State = ETankAimingState::OutOfAmmo;
	}
	else if (IsReloading())
	{
		State = ETankAimingState::Reloading;
	}
	else if (IsAiming())
	{
		State = ETankAimingState::Aiming;
	}
	else
	{
		State = ETankAimingState::Locked;
	}
}

void UTankAimingComponent::Initialize(UTankBarrelComponent* NewBarrel, UTankTurretComponent* NewTurret)
{
	BarrelRef = NewBarrel;
	TurretRef = NewTurret;
}

void UTankAimingComponent::AimAtLocation(FVector Location)
{
	if (!ensure(BarrelRef && TurretRef)) { return; }
	
	FVector LaunchVelocity = { 0.0f, 0.0f, 0.0f };
	FVector StartLocation = BarrelRef->GetSocketLocation(FName("Muzzle"));

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());

	bool bSolutionFound = UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		StartLocation,
		Location,
		InitialProjectileSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,
		ActorsToIgnore,
		false
	);

	if (bSolutionFound)
	{
		AimDirection = LaunchVelocity.GetSafeNormal();

		MoveToAimTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveToAimTowards(FVector TargetDirection)
{
	if (!ensure(BarrelRef && TurretRef)) { return; }

	auto CurrentRotation = BarrelRef->GetForwardVector().Rotation();
	auto TargetRotation = TargetDirection.Rotation();
	auto DeltaRotation = TargetRotation - CurrentRotation;

	float BarrelRotation = DeltaRotation.Pitch;
	float TurretRotation = DeltaRotation.Yaw;

	if (FMath::Abs(TurretRotation) > 180.0f)
	{
		TurretRotation *= -1;
	}

	BarrelRef->Elevate(BarrelRotation);
	TurretRef->Rotate(TurretRotation);
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Projectile && BarrelRef)) { return; }

	if (State == ETankAimingState::Reloading || State == ETankAimingState::OutOfAmmo) { return; }

	AProjectile* NewProjectile = GetWorld()->SpawnActor<AProjectile>(
		Projectile,
		BarrelRef->GetSocketLocation(FName("Muzzle")),
		BarrelRef->GetSocketRotation(FName("Muzzle"))
		);

	NewProjectile->Launch(InitialProjectileSpeed);

	LastFireTime = FPlatformTime::Seconds();
	--CurrentNumberOfAmmo;
}

bool UTankAimingComponent::IsOutOfAmmo() const
{
	return CurrentNumberOfAmmo == 0;
}

bool UTankAimingComponent::IsReloading() const
{
	return (FPlatformTime::Seconds() - LastFireTime) < ReloadSpeed;
}

bool UTankAimingComponent::IsAiming() const
{
	if (!ensure(BarrelRef)) { return false; }

	return !AimDirection.Equals(BarrelRef->GetForwardVector().GetSafeNormal(), 0.01);
}

ETankAimingState UTankAimingComponent::GetState() const
{
	return State;
}

int32 UTankAimingComponent::GetMaxNumberOfAmmo() const
{
	return MaxNumberOfAmmo;
}

int32 UTankAimingComponent::GetCurrentNumberOfAmmo() const
{
	return CurrentNumberOfAmmo;
}

UTankBarrelComponent* UTankAimingComponent::GetBarrelRef() const
{
	return BarrelRef;
}

UTankTurretComponent* UTankAimingComponent::GetTurretRef() const
{
	return TurretRef;
}
