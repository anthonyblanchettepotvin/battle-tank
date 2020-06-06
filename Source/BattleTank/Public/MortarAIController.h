// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MortarAIController.generated.h"

class ATank;
class UTankAimingComponent;

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

protected:
	// Properties
	/** Reference to the TankAimingComponent on the possessed pawn. */
	UPROPERTY(BlueprintReadOnly)
		UTankAimingComponent* AimingComponentRef = nullptr;

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
	UFUNCTION()
		virtual void HandleOnDeath();
};
