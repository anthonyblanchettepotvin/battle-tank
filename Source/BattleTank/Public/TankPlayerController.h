// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

// Forward declarations
class ATank;

/**
 * TankPlayerController is the base PlayerController for a Tank.
 * @see APlayerController
 * @see ATank
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

	// Constructors
public:
	/** Default constructor for ATankPlayerController. */
	ATankPlayerController();

	// Properties
private:
	/** Crosshair position in the viewport in percentage. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controller", meta = (AllowPrivateAccess = true, ClampMin = 0, ClampMax = 1))
		FVector2D CrosshairPosition = { 0.5f, 0.33f };

	// ~ Begin APlayerController Interface
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn) override;
	// ~ End APlayerController Interface

	// Functions
public:
	/** Make the controlled Tank aim at the world space location where the player's crosshair is aiming. */
	UFUNCTION(BlueprintCallable, Category = "Controller")
		virtual void AimTowardsCrosshair();

	/**
	 * Get the world space location where the player's crosshair is aiming.
	 * @param OutLocation The world space location where the player's crosshair is aiming
	 * @return TRUE if the player's crosshair is aiming at something, FALSE otherwise
	 */
	UFUNCTION(BlueprintCallable, Category = "Controller")
		virtual bool CrosshairToWorldLocation(FVector& OutLocation) const;

private:
	/**
	 * Handle OnDeath broadcast from controlled Tank.
	 * @see ATank
	 */
	UFUNCTION()
		void HandleTankOnDeath();

	// Events
public:
	/**
	 * Event called at the end of BeginPlay.
	 * @see BeginPlay()
	 */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Controller")
		void OnBeginPlayEnd();

	// Getters/setters
public:
	/** Getter for ControlledTank */
	UFUNCTION(BlueprintPure, Category = "Controller")
		ATank* GetControlledTank() const;
};
