// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialize(UTankTrackComponent* NewLeftTrack, UTankTrackComponent* NewRightTrack)
{
	LeftTrackRef = NewLeftTrack;
	RightTrackRef = NewRightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Force)
{
	if (!LeftTrackRef || !RightTrackRef) { return; }

	float ClampedForce = FMath::Clamp(Force, -1.0f, 1.0f);

	LeftTrackRef->SetThrottle(ClampedForce);
	RightTrackRef->SetThrottle(ClampedForce);
}

void UTankMovementComponent::IntendTurnRight(float Force)
{
	if (!LeftTrackRef || !RightTrackRef) { return; }

	float ClampedForce = FMath::Clamp(Force, -1.0f, 1.0f);

	LeftTrackRef->SetThrottle(ClampedForce);
	RightTrackRef->SetThrottle(-ClampedForce);
}
