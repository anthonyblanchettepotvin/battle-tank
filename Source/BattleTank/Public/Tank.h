// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankMovementComponent;
class UTankBarrelComponent;
class UTankTurretComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	/** Default constructor for ATank. */
	ATank();

private:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Tank, meta = (AllowPrivateAccess = true))
		UTankAimingComponent* AimingComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Tank, meta = (AllowPrivateAccess = true))
		UTankMovementComponent* MovementComponent = nullptr;

protected:
	// Properties
	/** The projectile to be fired by the tank. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tank|Firing")
		TSubclassOf<AProjectile> Projectile = nullptr;

	/** The initial speed of the projectile being fired by the tank. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tank|Firing")
		float InitialProjectileSpeed = 10000;

	/** The time is takes in seconds for the tank to load a projectile. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tank|Firing")
		float ReloadSpeed = 3.0f;

	/** The last time, in seconds since the beginning of the game, that the tank fired a projectile. */
	double LastFireTime = 0.0;

	// Functions
	// ~ Begin APawn Interface
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// ~ End APawn Interface

	/**
	 * Make the tank aim at a location.
	 * @param Location The location at which the tank should aim
	 */
	virtual void AimAt(FVector Location);

	/** 
	 * Make the tank fire a projectile. 
	 */
	UFUNCTION(BlueprintCallable, Category = Tank)
		virtual void Fire();

	// Setters/getters
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Tank)
		bool IsReloaded() const;
};
