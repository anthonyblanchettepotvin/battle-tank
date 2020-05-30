// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrackComponent;

/**
 * TankMovementComponent defines functionnality for moving a Tank.
 * @see ATank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

private:
	/** Reference to the left track of the tank. */
	UPROPERTY()
		UTankTrackComponent* LeftTrackRef = nullptr;

	/** Reference to the right track of the tank. */
	UPROPERTY()
		UTankTrackComponent* RightTrackRef = nullptr;

public:
	// Functions
	/**
	 * Initialize the movement component by providing the required component.
	 * @param NewLeftTrack The TankTrackComponent for the left track of the tank
	 * @param NewRightTrack The UTankTrackComponent for the right track of the tank
	 * @see UTankTrackComponent
	 */
	UFUNCTION(BlueprintCallable, Category = TankMovement)
		void Initialize(UTankTrackComponent* NewLeftTrack, UTankTrackComponent* NewRightTrack);

	/** 
	 * Signal the movement component to move the tank forward.
	 * @param Force The amount of force between [-1..1] with which the tank should move
	 * @note The Force is clamped between [-1..] where 1 is the equivalent of 100% and -1 is the equivalent of -100%.
	 * @note Negative value will invert the action, meaning that the tank will move backward.
	 */
	UFUNCTION(BlueprintCallable, Category = TankMovement)
		void IntendMoveForward(float Force);

	/**
	 * Signal the movement component to turn the tank to the right.
	 * @param Force The amount of force between [-1..1] with which the tank should move
	 * @note The Force is clamped between [-1..] where 1 is the equivalent of 100% and -1 is the equivalent of -100%.
	 * @note Negative value will invert the action, meaning that the tank will turn to the left.
	 */
	UFUNCTION(BlueprintCallable, Category = TankMovement)
		void IntendTurnRight(float Force);
};
