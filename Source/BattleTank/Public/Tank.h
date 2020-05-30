// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
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

protected:
	// Properties
	/** The projectile to be fired by the tank. */
	UPROPERTY(EditAnywhere, Category = "Tank|Firing")
		TSubclassOf<AProjectile> Projectile = nullptr;

	/** The initial speed of the projectile being fired by the tank. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank|Firing")
		float InitialProjectileSpeed = 10000;

	/** Reference to the barrel component of the tank. */
	UTankBarrelComponent* Barrel = nullptr;

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
	UFUNCTION(BlueprintCallable, Category = Tank)
		void SetBarrelComponentReference(UTankBarrelComponent* Value);

	UFUNCTION(BlueprintCallable, Category = Tank)
		void SetTurretComponentReference(UTankTurretComponent* value);
};
