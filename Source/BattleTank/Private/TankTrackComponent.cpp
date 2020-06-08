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

void UTankTrackComponent::SetThrottle(float Value)
{
	float Throttle = FMath::Clamp<float>(Value, -1.0f, 1.0f);

	ApplyDrivingForce(Throttle);
}

TArray<ASprungWheel*> UTankTrackComponent::GetWheels() const
{
	TArray<ASprungWheel*> Wheels;
	TArray<USceneComponent*> Children;

	GetChildrenComponents(false, Children);

	for (USceneComponent* Child : Children)
	{
		USpawnPoint* SpawnPoint = Cast<USpawnPoint>(Child);
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

void UTankTrackComponent::ApplyDrivingForce(float Throttle)
{
	TArray<ASprungWheel*> Wheels = GetWheels();

	float ForceApplied = Throttle * MaxDrivingForce;
	float ForcePerWheel = ForceApplied / Wheels.Num();

	for (ASprungWheel* Wheel : Wheels)
	{
		if (Wheel)
		{
			Wheel->AddDrivingForce(ForcePerWheel);
		}
	}
}
