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

	EvaluateState();
}

void UTankAimingComponent::Initialize(UTankBarrelComponent* NewBarrel, UTankTurretComponent* NewTurret)
{
	BarrelRef = NewBarrel;
	TurretRef = NewTurret;
}

void UTankAimingComponent::AimAtLocation(const FVector Location)
{
	if (!BarrelRef || !TurretRef) { return; }
	
	FVector LaunchVelocity = { 0.0f, 0.0f, 0.0f };
	const FVector StartLocation = BarrelRef->GetSocketLocation(FName("Muzzle"));
	const TArray<AActor*> ActorsToIgnore = {GetOwner()};
	const bool bSolutionFound = UGameplayStatics::SuggestProjectileVelocity(
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

void UTankAimingComponent::EvaluateState_Implementation()
{
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

void UTankAimingComponent::MoveToAimTowards_Implementation(const FVector TargetDirection)
{
	if (!BarrelRef || !TurretRef) { return; }

	const auto CurrentRotation = BarrelRef->GetForwardVector().Rotation();
	const auto TargetRotation = TargetDirection.Rotation();
	const auto DeltaRotation = TargetRotation - CurrentRotation;

	const float BarrelRotation = DeltaRotation.Pitch;
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
	if (!Projectile || !BarrelRef) { return; }

	if (State == ETankAimingState::Reloading || State == ETankAimingState::OutOfAmmo) { return; }

	AProjectile* NewProjectile = GetWorld()->SpawnActor<AProjectile>(
		Projectile,
		BarrelRef->GetSocketLocation(FName("Muzzle")),
		BarrelRef->GetSocketRotation(FName("Muzzle"))
		);

	NewProjectile->Launch(InitialProjectileSpeed);

	LastFireTime = FPlatformTime::Seconds();
	CurrentNumberOfAmmo--;
}

bool UTankAimingComponent::IsOutOfAmmo() const
{
	return CurrentNumberOfAmmo <= 0;
}

bool UTankAimingComponent::IsReloading() const
{
	return (FPlatformTime::Seconds() - LastFireTime) < ReloadSeconds;
}

bool UTankAimingComponent::IsAiming() const
{
	if (!BarrelRef) { return false; }

	return !AimDirection.Equals(BarrelRef->GetForwardVector().GetSafeNormal(), 0.01);
}

ETankAimingState UTankAimingComponent::GetState() const
{
	return State;
}

FVector UTankAimingComponent::GetAimDirection() const
{
	return AimDirection;
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
