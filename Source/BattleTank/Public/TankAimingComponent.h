// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingStateEnum.h"
#include "TankAimingComponent.generated.h"

// Forward definitions
class AProjectile;
class UTankBarrelComponent;
class UTankTurretComponent;

/** 
 * TankAimingComponent handles the aiming and firing of a Tank.
 * @see ATank
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

	// Constructors
public:
	/** Default constructor for UTankAimingComponent. */
	UTankAimingComponent();

	// Properties
private:
	/**
	 * Current state of the aiming process.
	 * @see ETankAimingState 
	 */
	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetState, Category = "TankAimingComponent|Aiming", meta = (AllowPrivateAccess = true))
		ETankAimingState State = ETankAimingState::Aiming;

	/** The aim direction based on the player's aim location and the suggested projectile velocity. */
	UPROPERTY(BlueprintGetter = GetAimDirection, Category = "TankAimingComponent|Aiming", meta = (AllowPrivateAccess = true))
		FVector AimDirection = { 0.0f, 0.0f, 0.0f };

	/**
	 * The Projectile to be fired.
	 * @see AProjectile 
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TankAimingComponent|Firing", meta = (AllowPrivateAccess = true))
		TSubclassOf<AProjectile> Projectile = nullptr;

	/** The initial speed of the projectile being fired. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TankAimingComponent|Firing", meta = (AllowPrivateAccess = true))
		float InitialProjectileSpeed = 10000;

	/** The time is takes in seconds to reload a projectile. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TankAimingComponent|Firing", meta = (AllowPrivateAccess = true))
		float ReloadSeconds = 3.0f;

	/** The last time, in seconds since the beginning of the game, that a projectile has been fired. */
	UPROPERTY()
		double LastFireTime = 0.0;

	/** The maximum number of ammunitions that can be fired. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintGetter = GetMaxNumberOfAmmo, Category = "TankAimingComponent|Firing", meta = (AllowPrivateAccess = true))
		int32 MaxNumberOfAmmo = 10;

	/** The current number of ammunitions that can be fired. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintGetter = GetCurrentNumberOfAmmo, Category = "TankAimingComponent|Firing", meta = (AllowPrivateAccess = true))
		int32 CurrentNumberOfAmmo = 0;

	/**
	 * Reference to the TankBarrelComponent of the owning Tank.
	 * @note This is set by calling Initialize()
	 * @see UTankBarrelComponent
	 * @see Initialize(UTankBarrelComponent* NewBarrel, UTankTurretComponent* NewTurret)
	 */
	UPROPERTY(BlueprintGetter = GetBarrelRef, Category = "TankAimingComponent")
		UTankBarrelComponent* BarrelRef = nullptr;

	/**
	 * Reference to the TankTurretComponent of the owning Tank.
	 * @note This is set by calling Initialize()
	 * @see UTankTurretComponent
	 * @see Initialize(UTankBarrelComponent* NewBarrel, UTankTurretComponent* NewTurret)
	 */
	UPROPERTY(BlueprintGetter = GetTurretRef, Category = "TankAimingComponent")
		UTankTurretComponent* TurretRef = nullptr;

	// ~ Start UActorComponent Interface
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// ~ End UActorComponent Interface

	// Functions
public:
	/**
	 * Initialize the component by providing the required components.
	 * @note Need to be called in order to make the component functionnal.
	 * @param NewBarrel The TankBarrelComponent for the barrel of the tank
	 * @param NewTurret The TankTurretComponent for the turret of the tank
	 * @see UTankBarrelComponent
	 * @see UTankTurretComponent
	 */
	UFUNCTION(BlueprintCallable, Category = "TankAimingComponent")
		virtual void Initialize(UTankBarrelComponent* NewBarrel, UTankTurretComponent* NewTurret);

	/** Tell the component to fire a projectile. */
	UFUNCTION(BlueprintCallable, Category = "TankAimingComponent|Firing")
		virtual void Fire();

	/**
	 * Tell the component to make the tank aim at a location.
	 * @param TargetLocation The location at which the tank should aim
	 */
	UFUNCTION(BlueprintCallable, Category = "TankAimingComponent|Aiming")
		virtual void AimAtLocation(const FVector TargetLocation);

protected:
	/** 
	 * Change State based on the state of the component.
	 * @see State
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "TankAimingComponent|Aiming")
		void EvaluateState();
	virtual void EvaluateState_Implementation();

	/**
	 * Tell the component to move the barrel and the turret in order to aim towards a direction.
	 * @param TargetDirection The direction to aim at
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "TankAimingComponent|Aiming")
		void MoveToAimTowards(const FVector TargetDirection);
	virtual void MoveToAimTowards_Implementation(const FVector TargetDirection);

	// Getters/setters
public:
	/**
	 * Whether or not the barrel is in the process of aiming in the AimDirection.
	 * @see AimDirection
	 */
	UFUNCTION(BlueprintPure, Category = "TankAimingComponent|Aiming")
		bool IsAiming() const;

	/** Whether or not the tank is out of ammunitions. */
	UFUNCTION(BlueprintPure, Category = "TankAimingComponent|Firing")
		bool IsOutOfAmmo() const;

	/** Whether or not the projectile is reloading. */
	UFUNCTION(BlueprintPure, Category = "TankAimingComponent|Firing")
		bool IsReloading() const;

	/** Getter for State */
	UFUNCTION(BlueprintPure, Category = "TankAimingComponent|Aiming")
		ETankAimingState GetState() const;

	/** Getter for AimDirection */
	UFUNCTION(BlueprintPure, Category = "TankAimingComponent|Aiming")
		FVector GetAimDirection() const;

	/** Getter for MaxNumberOfAmmo */
	UFUNCTION(BlueprintPure, Category = "TankAimingComponent|Firing")
		int32 GetMaxNumberOfAmmo() const;

	/** Getter for CurrentNumberOfAmmo */
	UFUNCTION(BlueprintPure, Category = "TankAimingComponent|Firing")
		int32 GetCurrentNumberOfAmmo() const;

	/** Getter for BarrelRef */
	UFUNCTION(BlueprintPure, Category = "TankAimingComponent")
		UTankBarrelComponent* GetBarrelRef() const;

	/** Getter for TurretRef */
	UFUNCTION(BlueprintPure, Category = "TankAimingComponent")
		UTankTurretComponent* GetTurretRef() const;
};
