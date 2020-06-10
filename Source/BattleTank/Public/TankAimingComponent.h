// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingStateEnum.h"
#include "TankAimingComponent.generated.h"

class AProjectile;
class UTankBarrelComponent;
class UTankTurretComponent;

/** 
 * TankAimingComponent handles the aiming and firing of a Tank pawn.
 * @see ATank
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Default constructor for UTankAimingComponent. */
	UTankAimingComponent();

private:
	// Properties
	/** Reference to the TankBarrelComponent of the owning Tank. */
	UPROPERTY(BlueprintGetter = GetBarrelRef)
		UTankBarrelComponent* BarrelRef = nullptr;

	/** Reference to the TankTurretComponent of the owning Tank. */
	UPROPERTY(BlueprintGetter = GetTurretRef)
		UTankTurretComponent* TurretRef = nullptr;

protected:
	/** Current state of the aiming process for the owning Tank. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintGetter = GetState, Category = "TankAimingComponent|Aiming")
		ETankAimingState State = ETankAimingState::Aiming;

	/** The Projectile to be fired by the owning Tank. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TankAimingComponent|Firing")
		TSubclassOf<AProjectile> Projectile = nullptr;

	/** The initial speed of the projectile being fired by the owning Tank. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TankAimingComponent|Firing")
		float InitialProjectileSpeed = 10000;

	/** The time is takes in seconds for the tank to load a projectile. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TankAimingComponent|Firing")
		float ReloadSpeed = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintGetter = GetMaxNumberOfAmmo, Category = "TankAimingComponent|Firing")
		int32 MaxNumberOfAmmo = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintGetter = GetCurrentNumberOfAmmo, Category = "TankAimingComponent|Firing")
		int32 CurrentNumberOfAmmo = 0;

	/** The last time, in seconds since the beginning of the game, that the owning tank fired a projectile. */
	double LastFireTime = 0.0;

	/** The aim direction based on the player's aim location and the suggested projectile velocity. */
	FVector AimDirection = { 0.0f, 0.0f, 0.0f };

	// Functions
	// ~ Start UActorComponent Interface
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// ~ End UActorComponent Interface

	/**
	 * Initialize the aiming component by providing the required component.
	 * @param NewBarrel The TankBarrelComponent for the barrel of the tank
	 * @param NewTurret The TankTurretComponent for the turret of the tank
	 * @see UTankBarrelComponent
	 * @see UTankTurretComponent
	 */
	UFUNCTION(BlueprintCallable, Category = TankAimingComponent)
		void Initialize(UTankBarrelComponent* NewBarrel, UTankTurretComponent* NewTurret);

	/**
	 * Tell the component to make the tank aim at a location.
	 * @param Location The location at which the tank should aim
	 * @param InitialProjectileSpeed The initial speed at which a projectile is fired
	 */
	virtual void AimAt(FVector Location);

	/**
	 * Tell the component to move the barrel and the turret in order to aim towards a direction.
	 * @param AimDirection The direction to aim at
	 */
	virtual void MoveToAimTowards(FVector TargetDirection);

	/** Tell the component to fire a projectile. */
	UFUNCTION(BlueprintCallable, Category = "TankAimingComponent|Firing")
		virtual void Fire();

	// Getters/setters
	/** Whether or not the tank is out of ammunitions. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "TankAimingComponent|Firing")
		bool IsOutOfAmmo() const;

	/** Whether or not the projectile is reloading. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "TankAimingComponent|Firing")
		bool IsReloading() const;

	/** Whether or not the barrel is in the process of aiming in the AimDirection. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "TankAimingComponent|Aiming")
		bool IsAiming() const;

	/** Getter for State */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "TankAimingComponent|Firing")
		ETankAimingState GetState() const;

	/** Getter for MaxNumberOfAmmo */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "TankAimingComponent|Firing")
		int32 GetMaxNumberOfAmmo() const;

	/** Getter for CurrentNumberOfAmmo */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "TankAimingComponent|Firing")
		int32 GetCurrentNumberOfAmmo() const;

	/** Getter for BarrelRef */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = TankAimingComponent)
		UTankBarrelComponent* GetBarrelRef() const;

	/** Getter for TurretRef */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = TankAimingComponent)
		UTankTurretComponent* GetTurretRef() const;
};
