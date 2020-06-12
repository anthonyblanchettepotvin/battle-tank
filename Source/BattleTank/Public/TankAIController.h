// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

// Forward declarations
class ATank;

/**
 * TankAIController is the base AIController for a Tank.
 * @see AAIController
 * @see ATank
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

	// Constructors
public:
	/** Default constructor for ATankAIController. */
	ATankAIController();

	// Properties
private:
	/** Offset to add to the aim location. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controller", meta = (AllowPrivateAccess = true))
		FVector AimLocationOffset = { 0.0f, 0.0f, 100.0f };

	/** Radius within which the AI must be in order to be considered close enough to it's target. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controller|Pathfinding", meta = (AllowPrivateAccess = true))
		float AcceptanceRadius = 3000.0f;

	// ~ Start AAIController Interface
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn) override;
	// ~ End AAIController Interface

	// Functions
private:
	/**
	 * Handle OnDeath broadcast from controlled Tank.
	 * @see ATank
	 */
	UFUNCTION()
		void HandleOnTankDeath();

	// Getters/setters
public:
	/** Getter for ControlledTank */
	UFUNCTION(BlueprintPure, Category = "Controller")
		ATank* GetControlledTank() const;
};
