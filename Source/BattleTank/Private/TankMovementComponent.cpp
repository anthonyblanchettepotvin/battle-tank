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
	if (!ensure(LeftTrackRef && RightTrackRef)) { return; }

	float ClampedForce = FMath::Clamp(Force, -1.0f, 1.0f);

	LeftTrackRef->SetThrottle(ClampedForce);
	RightTrackRef->SetThrottle(ClampedForce);
}

void UTankMovementComponent::IntendTurnRight(float Force)
{
	if (!ensure(LeftTrackRef && RightTrackRef)) { return; }

	float ClampedForce = FMath::Clamp(Force, -1.0f, 1.0f);

	LeftTrackRef->SetThrottle(ClampedForce);
	RightTrackRef->SetThrottle(-ClampedForce);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector MoveDirection = MoveVelocity.GetSafeNormal();

	float ForwardForce = FVector::DotProduct(TankDirection, MoveDirection);
	float RightForce = FVector::CrossProduct(TankDirection, MoveDirection).Z;

	//UE_LOG(LogTemp, Warning, TEXT("%s - %s - RequestDirectMove - ForwardForce = %f"), *GetOwner()->GetName(), *GetName(), ForwardForce)
	//UE_LOG(LogTemp, Warning, TEXT("%s - %s - RequestDirectMove - RightForce = %f"), *GetOwner()->GetName(), *GetName(), RightForce)

	IntendMoveForward(ForwardForce);
	IntendTurnRight(RightForce);
}
