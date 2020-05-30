// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurretComponent.generated.h"

/**
 * TankTurretComponent implements the behavior of a tank turret.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurretComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	/**
	 * Returns the speed in degrees per second based on the relative speed.
	 *
	 * @param RelativeSpeed The relative speed [-1..1] at which the turret should move
	 * @return The speed in degrees per second
	 * @note The relative speed is clamped to [-1..1]
	 */
	float GetAngularSpeed(float RelativeSpeed);

	/**
	 * Rotate the turret by some degrees per second based on the relative speed.
	 *
	 * The degrees per second at which the turret will rotate is the product of
	 * the maximum degrees per second multiplied by the relative speed.
	 *
	 * @param RelativeSpeed The relative speed [-1..1] at which the turret should rotate
	 * @note The relative speed is clamped to [-1..1]
	 */
	void Rotate(FVector AimDirection);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
		float MaxDegreesPerSecond = 30.0f;
};
