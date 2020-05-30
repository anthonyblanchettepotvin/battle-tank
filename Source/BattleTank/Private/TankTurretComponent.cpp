// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurretComponent.h"
#include "DrawDebugHelpers.h"

float UTankTurretComponent::GetAngularSpeed(float RelativeSpeed)
{
	float ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);

	return ClampedRelativeSpeed * MaxDegreesPerSecond;
}

void UTankTurretComponent::Rotate(FVector AimDirection)
{
	FVector CurrDirection = GetRelativeRotation().Vector();

	DrawDebugDirectionalArrow(GetWorld(), GetComponentLocation(), GetComponentLocation() + (CurrDirection * 1000.0f), 20.0f, FColor::Blue, false, -1.0f, 0, 10.0f);

	// TODO: This code is repeated in UTankBarrelRotation
	FRotator CurrRotation = GetForwardVector().Rotation();
	FRotator AimRotation = AimDirection.Rotation();
	FRotator DeltaRotation = AimRotation - CurrRotation;

	// Absolute value, because we want the turret to rotate clockwise
	float RotationChange = FMath::Abs(GetAngularSpeed(DeltaRotation.Yaw) * GetWorld()->DeltaTimeSeconds);

	// Check if the turret is on the right or left side of aiming direction
	FVector RightDirection = GetRightVector();
	float Rightness = FVector::DotProduct(RightDirection, AimDirection);
	if (Rightness < 0) {
		// Turn anticlockwise
		RotationChange *= -1;
	}

	float CurrentYaw = GetRelativeRotation().Yaw;
	float NewYaw = CurrentYaw + RotationChange;

	FRotator NewRotation = { 0.0f, NewYaw, 0.0f };

	SetRelativeRotation(NewRotation);
}
