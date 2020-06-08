// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

// Forward declarations
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
		UStaticMeshComponent* WheelMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprung Wheel", meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* AxleMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprung Wheel", meta = (AllowPrivateAccess = true))
		UPhysicsConstraintComponent* SpringConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprung Wheel", meta = (AllowPrivateAccess = true))
		UPhysicsConstraintComponent* AxleConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprung Wheel", meta = (AllowPrivateAccess = true))
		UArrowComponent* RollingDirection = nullptr;

	// Functions
	// ~ Start AActor Interface
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	// ~ End AActor Interface

	void AddDrivingForce(float ForceMagnitude);

private:
	void ConstrainToParentActorRoot();
};
