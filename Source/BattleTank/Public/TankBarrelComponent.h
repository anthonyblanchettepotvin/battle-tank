// Copyright � 2020 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrelComponent.generated.h"

/**
 * TankBarrelComponent implements the behavior of a tank barrel.
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankBarrelComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

protected:
	// Properties
	/** The minimum elevation in degrees that the barrel can elevate. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Barrel)
		float MinElevationDegrees = 0.0f;

	/** The maximum elevation in degrees that the barrel can elevate. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Barrel)
		float MaxElevationDegrees = 30.0f;

	/** The maximum degrees per second the barrel can elevate. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Barrel)
		float MaxDegreesPerSecond = 10.0f;

public:
	// Functions
	/**
	 * Returns the speed in degrees per second based on the relative speed.
	 * @param RelativeSpeed The relative speed [-1..1] at which the barrel should move
	 * @return The speed in degrees per second
	 * @note The relative speed is clamped to [-1..1]
	 */
	float GetAngularSpeed(float RelativeSpeed);

	/**
	 * Elevate the barrel by some degrees per second based on the relative speed. 
	 * 
	 * The degrees per second at which the barrel will elevate is the product of
	 * the maximum degrees per second multiplied by the relative speed.
	 *
	 * @param RelativeSpeed The relative speed [-1..1] at which the barrel should move
	 * @note The relative speed is clamped to [-1..1]
	 */
	void Elevate(float RelativeSpeed);
};
