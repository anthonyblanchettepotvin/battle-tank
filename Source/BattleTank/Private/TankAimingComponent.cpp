// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#include "TankAimingComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrelComponent.h"
#include "TankTurretComponent.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::Initialize(UTankBarrelComponent* NewBarrel, UTankTurretComponent* NewTurret)
{
	BarrelRef = NewBarrel;
	TurretRef = NewTurret;
}

void UTankAimingComponent::AimAt(FVector Location)
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
		FVector AimDirection = LaunchVelocity.GetSafeNormal();

		DrawDebugDirectionalArrow(GetWorld(), StartLocation, StartLocation + (AimDirection * 1000.0f), 15.0f, FColor::Red, false, -1.0f, 0, 3.0f);

		MoveToAimTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveToAimTowards(FVector AimDirection)
{
	if (!ensure(BarrelRef && TurretRef)) { return; }

	auto BarrelRotation = BarrelRef->GetForwardVector().Rotation();
	auto AimRotation = AimDirection.Rotation();
	auto DeltaRotation = AimRotation - BarrelRotation;

	BarrelRef->Elevate(AimDirection);
	TurretRef->Rotate(AimDirection);
}

UTankBarrelComponent* UTankAimingComponent::GetBarrelRef() const
{
	return BarrelRef;
}

UTankTurretComponent* UTankAimingComponent::GetTurretRef() const
{
	return TurretRef;
}
