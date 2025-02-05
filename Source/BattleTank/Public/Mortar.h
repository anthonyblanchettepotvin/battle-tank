// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankAimingStateEnum.h"
#include "Mortar.generated.h"

// Forward declarations
class UHealthComponent;
class UTankAimingComponent;

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMortarDeathSignature);

/**
 * Mortar implements the behavior of a mortar (weapon).
 * @see "https://en.wikipedia.org/wiki/Mortar_(weapon)"
 */
UCLASS()
class BATTLETANK_API AMortar : public APawn
{
	GENERATED_BODY()

	// Constructors
public:
	/** Default constructor for AMortar. */
	AMortar();

	// Components
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintGetter = GetAimingComponent, Category = "Mortar", meta = (AllowPrivateAccess = true))
		UTankAimingComponent* AimingComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintGetter = GetHealthComponent, Category = "Mortar", meta = (AllowPrivateAccess = true))
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
	 * Tell the mortar to aim at a location.
	 * @param TargetLocation The location at which the mortar should aim
	 */
	UFUNCTION(BlueprintCallable, Category = "Mortar")
		virtual void AimAtLocation(const FVector TargetLocation);

	/** Tell the mortar to fire. */
	UFUNCTION(BlueprintCallable, Category = "Mortar")
		virtual void Fire();

private:
	/**
	 * Handle OnDeath broadcast from HealthComponent.
	 * @see UHealthComponent
	 */
	UFUNCTION()
		void HandleHealthComponentOnDeath();

	// Getters/setters
public:
	/** Getter for AimingState */
	UFUNCTION(BlueprintPure, Category = "Mortar")
		ETankAimingState GetAimingState() const;

	/** Getter for AimingComponent */
	UFUNCTION(BlueprintPure, Category = "Mortar")
		UTankAimingComponent* GetAimingComponent() const;

	/** Getter for HealthComponent */
	UFUNCTION(BlueprintPure, Category = "Mortar")
		UHealthComponent* GetHealthComponent() const;

	// Delegates
public:
	/** Called when the mortar has died. */
	UPROPERTY(BlueprintAssignable, Category = "Mortar")
		FOnMortarDeathSignature OnDeath;
};
