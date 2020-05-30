// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"

void UTankTrackComponent::SetThrottle(float Value)
{
	Throttle = FMath::Clamp<float>(Value, -1.0f, 1.0f);

	UE_LOG(LogTemp, Warning, TEXT("%s throttle set to %f"), *GetName(), Throttle);

	FVector ForceApplied = GetForwardVector() * Throttle * MaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();

	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	if (!TankRoot) { return; }

	UE_LOG(LogTemp, Warning, TEXT("%s throttle"), *GetName());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
