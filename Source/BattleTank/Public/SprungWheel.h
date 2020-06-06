// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

// Forward declarations
class UPhysicsConstraintComponent;

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
		UStaticMeshComponent* WheelMeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprung Wheel", meta = (AllowPrivateAccess = true))
		UPhysicsConstraintComponent* PhysicsConstraintComponent = nullptr;

	// Functions
	// ~ Start AActor Interface
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	// ~ End AActor Interface

private:
	void ConstrainToParentActorRoot();
};
