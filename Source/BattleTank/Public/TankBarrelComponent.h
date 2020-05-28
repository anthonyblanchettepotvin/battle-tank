// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrelComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankBarrelComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate(float DegreesPerSecond);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Barrel")
		float MinElevationDegrees = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Barrel")
		float MaxElevationDegrees = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Barrel")
		float MaxDegreesPerSecond = 10.0f;
};
