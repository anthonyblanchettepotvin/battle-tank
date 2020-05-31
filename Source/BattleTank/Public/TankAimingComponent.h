// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrelComponent;
class UTankTurretComponent;

UENUM()
enum class ETankAimingState : uint8
{
	Reloading,
	Aiming,
	Locked
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Default constructor for UTankAimingComponent. */
	UTankAimingComponent();

private:
	// Properties
	/** Reference to the barrel component of the owning tank. */
	UPROPERTY(BlueprintGetter = GetBarrelRef)
		UTankBarrelComponent* BarrelRef = nullptr;

	/** Reference to the turret component of the owning tank. */
	UPROPERTY(BlueprintGetter = GetTurretRef)
		UTankTurretComponent* TurretRef = nullptr;

protected:
	/** Current state of the aiming process for the owning tank. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Aiming)
		ETankAimingState State = ETankAimingState::Reloading;

public:
	/**
	 * Initialize the aiming component by providing the required component.
	 * @param NewBarrel The TankBarrelComponent for the barrel of the tank
	 * @param NewTurret The TankTurretComponent for the turret of the tank
	 * @see UTankBarrelComponent
	 * @see UTankTurretComponent
	 */
	UFUNCTION(BlueprintCallable, Category = TankMovement)
		void Initialize(UTankBarrelComponent* NewBarrel, UTankTurretComponent* NewTurret);

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
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Aiming)
		UTankBarrelComponent* GetBarrelRef() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Aiming)
		UTankTurretComponent* GetTurretRef() const;
};
