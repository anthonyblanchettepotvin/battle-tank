// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrackComponent.generated.h"

// Forward declarations
class ASprungWheel;

/**
 * TankTrackComponent implements the behavior of a Tank track.
 * @see ATank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrackComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

	// Constructors
public:
	UTankTrackComponent();

	// Properties
private:
	/** Max driving force in newtons applied by the track's motion. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Track", meta = (AllowPrivateAccess = true))
		float MaxDrivingForce = 400000.0f;

	// ~ Start UStaticMeshComponent Interface
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// ~ End UStaticMeshComponent Interface

	// Functions
private:
	/**
	 * Apply the MaxDrivingForce, multiplied by Throttle, in the forward direction of the track. 
	 * This simulates the track rolling and pulling/pushing the tank forward/backward.
	 * @param Throttle The intensity of the MaxDrivingForce to be applied
	 * @see MaxDrivingForce
	 * @note The Throttle is clamped to [-1..1]
	 */
	void ApplyDrivingForce(const float Throttle);

	// Getters/setters
public:
	/** Setter for Throlle */
	UFUNCTION(BlueprintCallable, Category = "Track")
		void SetThrottle(const float Value);

	/** Getter for Wheels */
	UFUNCTION(BlueprintPure, Category = "Track")
		TArray<ASprungWheel*> GetWheels() const;
};
