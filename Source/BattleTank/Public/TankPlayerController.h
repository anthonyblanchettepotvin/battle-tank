// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.generated.h"

/**
 * TankPlayerController is the base player controller for a Tank pawn.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	ATank* GetControlledTank() const;

private:
	/** Aim the tank's barrel at the location where the player's crosshair intersects the world. */
	void AimTowardsCrosshair();

	/** Get the world space location where the player's crosshair is aiming.
	 * @param OutAimLocation The world space location where the player's crosshair is aiming
	 * @return TRUE if the player's crosshair is aiming at something, FALSE otherwise
	 */
	bool GetCrosshairAimLocation(FVector& OutAimLocation) const;
};
