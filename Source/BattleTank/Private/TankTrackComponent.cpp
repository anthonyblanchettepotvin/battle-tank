// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#include "TankTrackComponent.h"
#include "DrawDebugHelpers.h"

UTankTrackComponent::UTankTrackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	OnComponentHit.AddDynamic(this, &UTankTrackComponent::OnComponentHitDelegate);
}

void UTankTrackComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTankTrackComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankTrackComponent::OnComponentHitDelegate(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplyDrivingForce();
	ApplySidewayForce();

	// We make sure Throttle is reset to zero since SetThrottle adds up all the values for the current frame.
	// This prevents the Throttle from staying at 1 or -1, thus applying full driving force at all time, even
	// when the player is not inputting anything.
	Throttle = 0.0f;
}

void UTankTrackComponent::SetThrottle(float Value)
{
	// We add the value to the current Throttle value since it could be set by multiple inputs for the current frame.
	// This prevents the Throttle from being reset to zero, since one of many inputs may not used, thus calling
	// SetThrottle with a value of 0.
	Throttle = FMath::Clamp<float>(Throttle + Value, -1.0f, 1.0f);
}

void UTankTrackComponent::ApplyDrivingForce()
{
	FVector ForceApplied = GetForwardVector() * Throttle * MaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();

	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	if (!ensure(TankRoot)) { return; }

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrackComponent::ApplySidewayForce()
{
	FVector RightVector = GetRightVector();
	FVector VelocityVector = GetComponentVelocity();
	//DrawDebugDirectionalArrow(GetWorld(), GetComponentLocation(), GetComponentLocation() + (RightVector.GetSafeNormal() * 200.0f), 15.0f, FColor::Black, false, -1.0f, 0, 5.0f);
	//DrawDebugDirectionalArrow(GetWorld(), GetComponentLocation(), GetComponentLocation() + VelocityVector, 15.0f, FColor::Black, false, -1.0f, 0, 5.0f);
	float SidewaySpeed = FVector::DotProduct(RightVector, VelocityVector);

	// We want to apply the force in the opposite direction, that's why we negate SidewayAcceleration
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector SidewayAcceleration = -SidewaySpeed * GetRightVector() / DeltaTime;

	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (!ensure(TankRoot)) { return; }

	// There is two tracks, that's why we divide by 2
	FVector SidewayForce = (TankRoot->GetMass() * SidewayAcceleration) / 2;
	//DrawDebugDirectionalArrow(GetWorld(), GetComponentLocation(), GetComponentLocation() + SidewayForce.GetSafeNormal(), 15.0f, FColor::Red, false, -1.0f, 0, 5.0f);

	TankRoot->AddForce(SidewayForce);
}
