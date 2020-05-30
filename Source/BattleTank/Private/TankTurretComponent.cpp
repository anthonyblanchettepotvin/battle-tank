// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurretComponent.h"

float UTankTurretComponent::GetAngularSpeed(float RelativeSpeed)
{
	float ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);

	return ClampedRelativeSpeed * MaxDegreesPerSecond;
}

void UTankTurretComponent::Rotate(float RelativeSpeed)
{
	float RotationChange = GetAngularSpeed(RelativeSpeed) * GetWorld()->DeltaTimeSeconds;

	float CurrentYaw = GetRelativeRotation().Yaw;
	float NewYaw = FMath::Fmod(CurrentYaw + RotationChange, 360.0f);

	FRotator NewRotation = { 0.0f, NewYaw, 0.0f };

	SetRelativeRotation(NewRotation);
}
