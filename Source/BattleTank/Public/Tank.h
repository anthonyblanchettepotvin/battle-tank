// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankMovementComponent;
class UHealthComponent;

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignatureTemp);

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Tank, meta = (AllowPrivateAccess = true))
		UHealthComponent* HealthComponent = nullptr;

protected:
	// Properties
	/** The maximum amount of health of the Tank. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank|Health")
		float MaxHealth = 100.0f;

	/** The current amount of health of the Tank. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank|Health")
		float CurrentHealth = 0.0f;

	// Getter/setters
	/** Getter for HealthPercentage */
	UFUNCTION(BlueprintPure, Category = "Tank|Health")
		float GetHealthPercentage() const;

	// Functions
	// ~ Begin APawn Interface
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	// ~ End APawn Interface

private:
	UFUNCTION()
		virtual void HandleOnDeath();

public:
	// Delegates
	/** Called when the Tank has died. */
	UPROPERTY(BlueprintAssignable, Category = "Tank|Health")
		FOnDeathSignatureTemp OnDeath;
};
