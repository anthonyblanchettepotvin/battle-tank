// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#include "TankMovementComponent.h"
#include "TankTrackComponent.h"

UTankMovementComponent::UTankMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	const FVector TankDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	const FVector MoveDirection = MoveVelocity.GetSafeNormal();

	const float ForwardForce = FVector::DotProduct(TankDirection, MoveDirection);
	const float RightForce = FVector::CrossProduct(TankDirection, MoveDirection).Z;

	IntendMoveForward(ForwardForce);
	IntendTurnRight(RightForce);
}

void UTankMovementComponent::Initialize(UTankTrackComponent* NewLeftTrack, UTankTrackComponent* NewRightTrack)
{
	LeftTrackRef = NewLeftTrack;
	RightTrackRef = NewRightTrack;
}

void UTankMovementComponent::IntendMoveForward_Implementation(const float Force)
{
	if (!LeftTrackRef || !RightTrackRef) { return; }

	const float ClampedForce = FMath::Clamp(Force, -1.0f, 1.0f);

	LeftTrackRef->SetThrottle(ClampedForce);
	RightTrackRef->SetThrottle(ClampedForce);
}

void UTankMovementComponent::IntendTurnRight_Implementation(const float Force)
{
	if (!LeftTrackRef || !RightTrackRef) { return; }

	const float ClampedForce = FMath::Clamp(Force, -1.0f, 1.0f);

	LeftTrackRef->SetThrottle(ClampedForce);
	RightTrackRef->SetThrottle(-ClampedForce);
}

UTankTrackComponent* UTankMovementComponent::GetLeftTrackRef() const
{
	return LeftTrackRef;
}

UTankTrackComponent* UTankMovementComponent::GetRightTrackRef() const
{
	return RightTrackRef;
}
