// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrelComponent;
class UTankTurretComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();



private:
	// Properties
	/** Reference to the barrel component of the owning tank. */
	UPROPERTY()
		UTankBarrelComponent* BarrelRef = nullptr;

	/** Reference to the turret component of the owning tank. */
	UPROPERTY()
		UTankTurretComponent* TurretRef = nullptr;

protected:
	// ~ Begin UActorComponent Interface
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// ~ End UActorComponent Interface

	// Functions
	/**
	 * Tell the component to make the tank aim at a location.
	 * @param Location The location at which the tank should aim
	 * @param InitialProjectileSpeed The initial speed at which a projectile is fired
	 */
	virtual void AimAt(FVector Location, float InitialProjectileSpeed);

	/**
	 * Tell the component to move the barrel and the turret in order to aim towards a direction.
	 * @param AimDirection The direction to aim at
	 */
	virtual void MoveToAimTowards(FVector AimDirection);

	// Getters/setters
	void SetBarrelComponentReference(UTankBarrelComponent* Value);

	void SetTurretComponentReference(UTankTurretComponent* Value);
};
