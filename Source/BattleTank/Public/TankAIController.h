// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
class UTankAimingComponent;

/**
 * TankPlayerController is the base AI controller for a Tank pawn.
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	/** Default constructor for ATankAIController. */
	ATankAIController();

protected:
	// Properties
	/** Radius that the AI must be in in order to be considered close enough to it's target. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controller|Pathfinding")
		float AcceptanceRadius = 3000.0f;

	/** Reference to the TankAimingComponent on the possessed pawn. */
	UPROPERTY(BlueprintReadOnly)
		UTankAimingComponent* AimingComponentRef = nullptr;

	// Functions
	// ~ Start AAIControllerInterface
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	// ~ End AAIControllerInterface
};
