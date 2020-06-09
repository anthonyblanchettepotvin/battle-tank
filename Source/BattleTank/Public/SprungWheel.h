// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

// Forward declarations
class USphereComponent;
class UPhysicsConstraintComponent;
class UArrowComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	/** Default constructor for ASprungWheel. */
	ASprungWheel();

private:
	// Components
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
	float TotalDrivingForce = 0.0f;

	// Functions
	// ~ Start AActor Interface
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	// ~ End AActor Interface

	void AddDrivingForce(float DrivingForce);

private:
	void ApplyDrivingForce();

	void ConstrainToParentActorRoot();

	// Delegates
	/**
	 * Delegate for WheelMesh's OnComponentHit
	 * @see WheelMesh
	 */
	UFUNCTION()
		void OnWheelMeshComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
