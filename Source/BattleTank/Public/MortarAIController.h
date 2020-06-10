// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MortarAIController.generated.h"

// Forward declarations
class AMortar;

/**
 * MortarAIController is the base AI controller for a Mortar pawn.
 */
UCLASS()
class BATTLETANK_API AMortarAIController : public AAIController
{
	GENERATED_BODY()

public:
	/** Default constructor for ATankAIController. */
	AMortarAIController();

	// Properties
private:
	bool bMortarIsDead = false;

	// Functions
protected:
	// ~ Start AAIControllerInterface
	virtual void BeginPlay() override;
	virtual void SetPawn(APawn* InPawn) override;

public:
	virtual void Tick(float DeltaTime) override;
	// ~ End AAIControllerInterface

private:
	/** Handle OnDeath broadcasts from possessed Mortar. */
	UFUNCTION()
		virtual void HandleOnMortarDeath();

	// Getters/setters
public:
	/** Getter for ControlledMortar */
	UFUNCTION(BlueprintPure, Category = "Controller")
		AMortar* GetControlledMortar() const;
};
