// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * TankPlayerController is the base player controller for a Tank pawn.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Properties
	/** Crosshair position in the viewport in percentage. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = TankPlayerController, meta = (ClampMin = 0, ClampMax = 1))
		FVector2D CrosshairPosition = { 0.5f, 0.33f };

	// Functions
	// ~ Begin APlayerController Interface
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	// ~ End APlayerController Interface

	// Getters/setters
	ATank* GetControlledTank() const;

private:
	/** Aim the tank's barrel at the location where the player's crosshair intersects the world. */
	void AimTowardsCrosshair();

	/**
	 * Get the world space location where the player's crosshair is aiming.
	 * @param OutAimLocation The world space location where the player's crosshair is aiming
	 * @return TRUE if the player's crosshair is aiming at something, FALSE otherwise
	 */
	bool GetCrosshairAimLocation(FVector& OutAimLocation) const;
};
