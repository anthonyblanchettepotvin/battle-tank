// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankMovementComponent;
class UHealthComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	/** Default constructor for ATank. */
	ATank();

private:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = true))
		UTankAimingComponent* AimingComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = true))
		UTankMovementComponent* MovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = true))
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

	// Getters/setters
	/** Getter for HealthComponent */
	UFUNCTION(BlueprintPure, Category = "Tank")
		UHealthComponent* GetHealthComponent() const;
};
