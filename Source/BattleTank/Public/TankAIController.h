// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

// Forward declarations
class ATank;

/**
 * TankAIController is the base AI controller for a Tank pawn.
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	/** Default constructor for ATankAIController. */
	ATankAIController();

	// Properties
protected:
	/** Radius that the AI must be in in order to be considered close enough to it's target. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controller|Pathfinding")
		float AcceptanceRadius = 3000.0f;

private:
	bool bTankIsDead = false;

	// Functions
protected:
	// ~ Start AAIController Interface
	virtual void BeginPlay() override;
	virtual void SetPawn(APawn* InPawn) override;

public:
	virtual void Tick(float DeltaTime) override;
	// ~ End AAIController Interface

private:
	/** Handle OnDeath broadcasts from possessed Tank. */
	UFUNCTION()
		virtual void HandleOnTankDeath();

	// Getters/setters
public:
	/** Getter for ControlledTank */
	UFUNCTION(BlueprintPure, Category = "Controller")
		ATank* GetControlledTank() const;
};
