// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#include "TankBarrelComponent.h"

UTankBarrelComponent::UTankBarrelComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankBarrelComponent::Elevate_Implementation(const float RelativeSpeed)
{
	const float PitchChange = CalculateAngularSpeed(RelativeSpeed) * GetWorld()->DeltaTimeSeconds;

	const float CurrentPitch = GetRelativeRotation().Pitch;
	float NewPitch = CurrentPitch + PitchChange;
	NewPitch = FMath::Clamp<float>(NewPitch, MinElevationDegrees, MaxElevationDegrees);

	const FRotator NewRotation = { NewPitch, 0.0f, 0.0f };

	SetRelativeRotation(NewRotation);
}

float UTankBarrelComponent::CalculateAngularSpeed(const float RelativeSpeed)
{
	const float ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);

	return MaxDegreesPerSecond * ClampedRelativeSpeed;
}
