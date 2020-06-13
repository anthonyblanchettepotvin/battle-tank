// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#include "TankTrackComponent.h"
#include "SpawnPoint.h"
#include "SprungWheel.h"

UTankTrackComponent::UTankTrackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrackComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTankTrackComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankTrackComponent::ApplyDrivingForce(const float Throttle)
{
	const TArray<ASprungWheel*> Wheels = GetWheels();

	const float ForceApplied = Throttle * MaxDrivingForce;
	const float ForcePerWheel = ForceApplied / Wheels.Num();

	for (ASprungWheel* Wheel : Wheels)
	{
		if (Wheel)
		{
			Wheel->AddDrivingForce(ForcePerWheel);
		}
	}
}

void UTankTrackComponent::SetThrottle(const float Value)
{
	const float Throttle = FMath::Clamp<float>(Value, -1.0f, 1.0f);

	ApplyDrivingForce(Throttle);
}

TArray<ASprungWheel*> UTankTrackComponent::GetWheels() const
{
	TArray<ASprungWheel*> Wheels;
	TArray<USceneComponent*> Children;

	GetChildrenComponents(false, Children);

	for (const USceneComponent* Child : Children)
	{
		const USpawnPoint* SpawnPoint = Cast<USpawnPoint>(Child);
		if (SpawnPoint)
		{
			ASprungWheel* Wheel = Cast<ASprungWheel>(SpawnPoint->GetSpawnedActor());
			if (Wheel)
			{
				Wheels.AddUnique(Wheel);
			}
		}
	}

	return Wheels;
}
