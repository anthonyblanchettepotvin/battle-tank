// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#include "TankMovementComponent.h"
#include "TankTrackComponent.h"

UTankMovementComponent::UTankMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

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

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector MoveDirection = MoveVelocity.GetSafeNormal();

	float FowardForce = FVector::DotProduct(TankDirection, MoveDirection);
	float RightForce = FVector::CrossProduct(TankDirection, MoveDirection).Z;

	IntendMoveForward(FowardForce);
	IntendTurnRight(RightForce);
}
