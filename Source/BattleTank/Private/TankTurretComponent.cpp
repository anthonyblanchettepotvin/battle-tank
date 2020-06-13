// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#include "TankTurretComponent.h"

UTankTurretComponent::UTankTurretComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTurretComponent::Rotate_Implementation(const float RelativeSpeed)
{
	const float YawChange = CalculateAngularSpeed(RelativeSpeed) * GetWorld()->DeltaTimeSeconds;

	const float CurrentYaw = GetRelativeRotation().Yaw;
	const float NewYaw = CurrentYaw + YawChange;

	const FRotator NewRotation = { 0.0f, NewYaw, 0.0f };

	SetRelativeRotation(NewRotation);
}

float UTankTurretComponent::CalculateAngularSpeed(float RelativeSpeed)
{
	const float ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);

	return MaxDegreesPerSecond * ClampedRelativeSpeed;
}
