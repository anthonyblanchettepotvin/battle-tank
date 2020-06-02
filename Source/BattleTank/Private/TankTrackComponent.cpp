// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#include "TankTrackComponent.h"

void UTankTrackComponent::SetThrottle(float Value)
{
	Throttle = FMath::Clamp<float>(Value, -1.0f, 1.0f);

	FVector ForceApplied = GetForwardVector() * Throttle * MaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();

	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	if (!ensure(TankRoot)) { return; }

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
