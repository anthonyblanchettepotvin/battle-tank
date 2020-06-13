// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

// Forward declarations
class UTankTrackComponent;

/**
 * TankMovementComponent defines functionnality for moving a Tank.
 * @see ATank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

	// Constructors
public:
	UTankMovementComponent();

	// Properties
private:
	/**
	 * Reference to the left TankTrackComponent of the owning Tank.
	 * @note This is set by calling Initialize()
	 * @see UTankTrackComponent
	 * @see Initialize(UTankTrackComponent* NewLeftTrack, UTankTrackComponent* NewRightTrack)
	 */
	UPROPERTY(BlueprintGetter = GetLeftTrackRef, Category = "TankMovementComponent")
		UTankTrackComponent* LeftTrackRef = nullptr;

	/**
	 * Reference to the right TankTrackComponent of the owning Tank.
	 * @note This is set by calling Initialize()
	 * @see UTankTrackComponent
	 * @see Initialize(UTankTrackComponent* NewLeftTrack, UTankTrackComponent* NewRightTrack)
	 */
	UPROPERTY(BlueprintGetter = GetRightTrackRef, Category = "TankMovementComponent")
		UTankTrackComponent* RightTrackRef = nullptr;

	// ~ Start UNavMovementComponent Interface
public:
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	// ~ End UNavMovementComponent Interface

	// Functions
public:
	/**
	 * Initialize the movement component by providing the required component.
	 * @note Need to be called in order to make the component functionnal.
	 * @param NewLeftTrack The TankTrackComponent for the left track of the tank
	 * @param NewRightTrack The TankTrackComponent for the right track of the tank
	 * @see UTankTrackComponent
	 */
	UFUNCTION(BlueprintCallable, Category = "TankMovementComponent")
		void Initialize(UTankTrackComponent* NewLeftTrack, UTankTrackComponent* NewRightTrack);

protected:
	/** 
	 * Signal the movement component to move the tank forward.
	 * @param Force The amount of force between [-1..1] with which the tank should move
	 * @note The Force is clamped between [-1..] where 1 is the equivalent of 100% and -1 is the equivalent of -100%.
	 * @note Negative value will invert the action, meaning that the tank will move backward.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "TankMovementComponent")
		void IntendMoveForward(const float Force);
	virtual void IntendMoveForward_Implementation(const float Force);

	/**
	 * Signal the movement component to turn the tank to the right.
	 * @param Force The amount of force between [-1..1] with which the tank should move
	 * @note The Force is clamped between [-1..] where 1 is the equivalent of 100% and -1 is the equivalent of -100%.
	 * @note Negative value will invert the action, meaning that the tank will turn to the left.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "TankMovementComponent")
		void IntendTurnRight(const float Force);
	virtual void IntendTurnRight_Implementation(const float Force);

	// Getters/setters
public:
	/** Getter for LeftTrackRef */
	UFUNCTION(BlueprintPure, Category = "TankMovementComponent")
		UTankTrackComponent* GetLeftTrackRef() const;

	/** Getter for RightTrackRef */
	UFUNCTION(BlueprintPure, Category = "TankMovementComponent")
		UTankTrackComponent* GetRightTrackRef() const;
};
