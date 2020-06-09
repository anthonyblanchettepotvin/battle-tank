// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Mortar.generated.h"

// Forward declarations
class UTankAimingComponent;
class UHealthComponent;

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMortarDeathSignature);

UCLASS()
class BATTLETANK_API AMortar : public APawn
{
	GENERATED_BODY()

public:
	/** Default constructor for AMortar. */
	AMortar();

private:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mortar", meta = (AllowPrivateAccess = true))
		UTankAimingComponent* AimingComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mortar", meta = (AllowPrivateAccess = true))
		UHealthComponent* HealthComponent = nullptr;

	// Functions
protected:
	// ~ Begin APawn Interface
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	// ~ End APawn Interface

private:
	/** Handle OnDeath broadcasts from HealthComponent. */
	UFUNCTION()
		void HandleHealthComponentOnDeath();

public:
	// Getters/setters
	/** Getter for HealthComponent */
	UFUNCTION(BlueprintPure, Category = "Mortar")
		UHealthComponent* GetHealthComponent() const;

	// Delegates
	/** Called when the mortar has died. */
	UPROPERTY(BlueprintAssignable, Category = "Mortar")
		FOnMortarDeathSignature OnDeath;
};
