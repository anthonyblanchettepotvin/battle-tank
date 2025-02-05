// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

// Forward declarations
class UArrowComponent;
class UPhysicsConstraintComponent;
class USphereComponent;

/** 
 * SprungWheel implements the behavior of a wheel with a spring and an axle.
 * It uses PhysicsConstraintComponent to create a realistic feel for the spring and the axle.
 * @see UPhysicsConstraintComponent
 */
UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()

	// Constructors
public:
	/** Default constructor for ASprungWheel. */
	ASprungWheel();

	// Components
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprung Wheel", meta = (AllowPrivateAccess = true))
		USceneComponent* Root = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprung Wheel", meta = (AllowPrivateAccess = true))
		USphereComponent* WheelMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprung Wheel", meta = (AllowPrivateAccess = true))
		USphereComponent* AxleMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprung Wheel", meta = (AllowPrivateAccess = true))
		UPhysicsConstraintComponent* SpringConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprung Wheel", meta = (AllowPrivateAccess = true))
		UPhysicsConstraintComponent* AxleConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprung Wheel", meta = (AllowPrivateAccess = true))
		UArrowComponent* RollingDirection = nullptr;

	// Properties
private:
	/**
	 * The total force to be applied on the wheel, in the direction of RollingDirection, this frame.
	 * @note The value is reset to zero at the end of each frame.
	 * @see RollingDirection
	 */
	UPROPERTY()
		float TotalDrivingForce = 0.0f;

	// ~ Start AActor Interface
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	// ~ End AActor Interface

	// Functions
public:
	/**
	 * Add an amount of force to TotalDrivingForce.
	 * @param DrivingForce The amount of force to add to TotalDrivingForce
	 * @see TotalDrivingForce
	 */
	UFUNCTION(BlueprintCallable, Category = "Sprung Wheel")
		virtual void AddDrivingForce(const float DrivingForce);

private:
	/**
	 * Apply the TotalDrivingForce on the wheel, in the direction of RollingDirection.
	 * @see TotalDrivingForce
	 */
	void ApplyDrivingForce();

	/**
	 * Find the parent Actor of the SprungWheel and constrain it's root component to AxleMesh with SpringConstraint.
	 * @see AActor#GetAttachParentActor()
	 * @see AxleMesh
	 * @see SpringConstraint
	 */
	void ConstrainToParentActorRoot();

	/**
	 * Handle OnComponentHit broadcast from WheelMesh.
	 * @see UPrimitiveComponent
	 */
	UFUNCTION()
		void HandleWheelMeshOnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
