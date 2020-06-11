// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankAimingStateEnum.h"
#include "Tank.generated.h"

// Forward declarations
class UHealthComponent;
class UTankAimingComponent;
class UTankMovementComponent;

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTankDeathSignature);

/**
 * Tank implements the behavior of a tank.
 * @see "https://en.wikipedia.org/wiki/Tank"
 */
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

	// Constructor
public:
	/** Default constructor for ATank. */
	ATank();

	// Components
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintGetter = GetAimingComponent, Category = "Tank", meta = (AllowPrivateAccess = true))
		UTankAimingComponent* AimingComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = true))
		UTankMovementComponent* MovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintGetter = GetHealthComponent, Category = "Tank", meta = (AllowPrivateAccess = true))
		UHealthComponent* HealthComponent = nullptr;

	// ~ Begin APawn Interface
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	// ~ End APawn Interface

	// Functions
public:
	/**
	 * Tell the tank to aim at a location.
	 * @param TargetLocation The location at which the tank should aim
	 */
	UFUNCTION(BlueprintCallable, Category = "Tank")
		virtual void AimAtLocation(const FVector TargetLocation);

	/** Tell the tank to fire. */
	UFUNCTION(BlueprintCallable, Category = "Tank")
		virtual void Fire();

private:
	/** Handle OnDeath broadcast from HealthComponent.*/
	UFUNCTION()
		void HandleHealthComponentOnDeath();

	// Getters/setters
public:
	/** Getter for AimingState */
	UFUNCTION(BlueprintPure, Category = "Tank")
		ETankAimingState GetAimingState() const;

	/** Getter for AimingComponent */
	UFUNCTION(BlueprintPure, Category = "Tank")
		UTankAimingComponent* GetAimingComponent() const;

	/** Getter for HealthComponent */
	UFUNCTION(BlueprintPure, Category = "Tank")
		UHealthComponent* GetHealthComponent() const;

	// Delegates
public:
	/** Called when the tank has died. */
	UPROPERTY(BlueprintAssignable, Category = "Tank")
		FOnTankDeathSignature OnDeath;
};
