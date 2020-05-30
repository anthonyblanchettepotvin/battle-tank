// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrackComponent.generated.h"

/**
 * TankTrackComponent implements the behavior of a tank track.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrackComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

protected:
	// Properties
	/** Max force in newtons output by the track. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Track)
		float MaxDrivingForce = 400000.0f; // Assume that the tank is 40 tons and acceleration is 1 g (9.81 m/s2)

	float Throttle = 0.0f;

public:
	// Getters/setters
	UFUNCTION(BlueprintCallable, Category = Track)
		void SetThrottle(float Value);
};
