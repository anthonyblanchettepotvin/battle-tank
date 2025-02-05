// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MortarAIController.generated.h"

// Forward declarations
class AMortar;

/**
 * MortarAIController is the base AIController for a Mortar.
 * @see AAIController
 * @see AMortar
 */
UCLASS()
class BATTLETANK_API AMortarAIController : public AAIController
{
	GENERATED_BODY()

	// Constructors
public:
	/** Default constructor for ATankAIController. */
	AMortarAIController();

	// Properties
public:
	/** Offset to add to the aim location. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controller", meta = (AllowPrivateAccess = true))
		FVector AimLocationOffset = { 0.0f, 0.0f, 100.0f };

	// ~ Start AAIControllerInterface
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn) override;
	// ~ End AAIControllerInterface

	// Functions
private:
	/**
	 * Handle OnDeath broadcast from controlled Mortar.
	 * @see AMortar
	 */
	UFUNCTION()
		void HandleOnMortarDeath();

	// Getters/setters
public:
	/** Getter for ControlledMortar */
	UFUNCTION(BlueprintPure, Category = "Controller")
		AMortar* GetControlledMortar() const;
};
