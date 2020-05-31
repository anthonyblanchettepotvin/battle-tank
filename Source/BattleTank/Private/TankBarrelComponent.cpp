// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#include "TankBarrelComponent.h"
#include "DrawDebugHelpers.h"

void UTankBarrelComponent::Elevate(FVector AimDirection)
{
	FVector CurrDirection = GetSocketRotation(FName("Muzzle")).Vector();

	DrawDebugDirectionalArrow(GetWorld(), GetComponentLocation(), GetComponentLocation() + (CurrDirection * 1000.0f), 15.0f, FColor::Purple, false, -1.0f, 0, 3.0f);

	// TODO: This code is repeated in UTankTurretRotation
	FRotator CurrRotation = GetForwardVector().Rotation();
	FRotator AimRotation = AimDirection.Rotation();
	FRotator DeltaRotation = AimRotation - CurrRotation;
	
	float ElevationChange = GetAngularSpeed(DeltaRotation.Pitch) * GetWorld()->DeltaTimeSeconds;

	float CurrentElevation = GetRelativeRotation().Pitch;
	float NewElevation = CurrentElevation + ElevationChange;
	NewElevation = FMath::Clamp<float>(NewElevation, MinElevationDegrees, MaxElevationDegrees);

	FRotator NewRotation = { NewElevation, 0.0f, 0.0f };

	SetRelativeRotation(NewRotation);
}

float UTankBarrelComponent::GetAngularSpeed(float RelativeSpeed)
{
	float ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);

	return MaxDegreesPerSecond * ClampedRelativeSpeed;
}
