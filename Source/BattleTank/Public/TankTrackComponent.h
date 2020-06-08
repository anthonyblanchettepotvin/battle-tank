// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrackComponent.generated.h"

// Forward declarations
class ASprungWheel;

/**
 * TankTrackComponent implements the behavior of a tank track.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrackComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UTankTrackComponent();

protected:
	// Properties
	/** Max force in newtons output by the track. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Track")
		float MaxDrivingForce = 400000.0f; // Assume that the tank is 40 tons and acceleration is 1 g (9.81 m/s2)

	// Functions
	// ~ Start UStaticMeshComponent Interface
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// ~ End UStaticMeshComponent Interface

	// Getters/setters
	/** Setter for Throlle */
	UFUNCTION(BlueprintCallable, Category = "Track")
		void SetThrottle(float Value);

	/** Getter for Wheels */
	UFUNCTION(BlueprintPure, Category = "Track")
		TArray<ASprungWheel*> GetWheels() const;

private:
	/**
	 * Apply a force in the forward/backward direction of the track. 
	 * This simulates the track rolling and pulling/pushing the tank forward/backward. 
	 * A Throttle of -1 means the track is pushing the tank backward. 
	 * A Throttle of 1 means the track is pulling the tank forward.
	 */
	void ApplyDrivingForce(float Throttle);
};
