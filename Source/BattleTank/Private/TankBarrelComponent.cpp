// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrelComponent.h"

void UTankBarrelComponent::Elevate(float RelativeSpeed)
{
	float CurrentElevation = GetRelativeRotation().Pitch;
	float ElevationChange = GetAngularSpeed(RelativeSpeed) * GetWorld()->DeltaTimeSeconds;

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
