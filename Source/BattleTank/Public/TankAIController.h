// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

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

	// Functions
protected:
	// ~ Start AAIControllerInterface
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	// ~ End AAIControllerInterface

	// Getters/setters
	ATank* GetControlledTank() const;

	ATank* GetPlayerTank() const;
};
