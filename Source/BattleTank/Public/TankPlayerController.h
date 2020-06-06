// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Controller, meta = (ClampMin = 0, ClampMax = 1))
		FVector2D CrosshairPosition = { 0.5f, 0.33f };

	/** Reference to the TankAimingComponent on the possessed pawn. */
	UPROPERTY(BlueprintReadOnly)
		UTankAimingComponent* AimingComponentRef = nullptr;

	// Functions
	// ~ Begin APlayerController Interface
	virtual void BeginPlay() override;
	virtual void SetPawn(APawn* InPawn) override;

public:
	virtual void Tick(float DeltaTime) override;
	// ~ End APlayerController Interface

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = Controller)
		void AfterBeginPlay();

protected:
	UFUNCTION()
	virtual void HandleOnDeath();

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
