// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#include "TankBarrelComponent.h"

void UTankBarrelComponent::Elevate(float RelativeSpeed)
{
	float PitchChange = GetAngularSpeed(RelativeSpeed) * GetWorld()->DeltaTimeSeconds;

	float CurrentPitch = GetRelativeRotation().Pitch;
	float NewPitch = CurrentPitch + PitchChange;
	NewPitch = FMath::Clamp<float>(NewPitch, MinElevationDegrees, MaxElevationDegrees);

	FRotator NewRotation = { NewPitch, 0.0f, 0.0f };

	SetRelativeRotation(NewRotation);
}

float UTankBarrelComponent::GetAngularSpeed(float RelativeSpeed)
{
	float ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);

	return MaxDegreesPerSecond * ClampedRelativeSpeed;
}
