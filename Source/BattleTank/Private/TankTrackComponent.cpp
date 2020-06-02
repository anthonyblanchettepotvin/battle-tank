// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#include "TankTrackComponent.h"
#include "DrawDebugHelpers.h"

UTankTrackComponent::UTankTrackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrackComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector RightVector = GetRightVector();
	FVector VelocityVector = GetComponentVelocity();
	//DrawDebugDirectionalArrow(GetWorld(), GetComponentLocation(), GetComponentLocation() + (RightVector.GetSafeNormal() * 200.0f), 15.0f, FColor::Black, false, -1.0f, 0, 5.0f);
	//DrawDebugDirectionalArrow(GetWorld(), GetComponentLocation(), GetComponentLocation() + VelocityVector, 15.0f, FColor::Black, false, -1.0f, 0, 5.0f);
	float SidewaySpeed = FVector::DotProduct(RightVector, VelocityVector);

	// We want to apply the force in the opposite direction, that's why we negate SidewayAcceleration
	FVector SidewayAcceleration = -SidewaySpeed * GetRightVector() / DeltaTime;

	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (!ensure(TankRoot)) { return; }

	// There is two tracks, that's why we divide by 2
	FVector SidewayForce = (TankRoot->GetMass() * SidewayAcceleration) / 2;

	//DrawDebugDirectionalArrow(GetWorld(), GetComponentLocation(), GetComponentLocation() + SidewayForce.GetSafeNormal(), 15.0f, FColor::Red, false, -1.0f, 0, 5.0f);

	TankRoot->AddForce(SidewayForce);
}

void UTankTrackComponent::SetThrottle(float Value)
{
	Throttle = FMath::Clamp<float>(Value, -1.0f, 1.0f);

	FVector ForceApplied = GetForwardVector() * Throttle * MaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();

	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	if (!ensure(TankRoot)) { return; }

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
