// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#include "TankTurretComponent.h"

void UTankTurretComponent::Rotate(float RelativeSpeed)
{
	float YawChange = GetAngularSpeed(RelativeSpeed) * GetWorld()->DeltaTimeSeconds;

	float CurrentYaw = GetRelativeRotation().Yaw;
	float NewYaw = CurrentYaw + YawChange;

	FRotator NewRotation = { 0.0f, NewYaw, 0.0f };

	SetRelativeRotation(NewRotation);
}

float UTankTurretComponent::GetAngularSpeed(float RelativeSpeed)
{
	float ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);

	return ClampedRelativeSpeed * MaxDegreesPerSecond;
}
