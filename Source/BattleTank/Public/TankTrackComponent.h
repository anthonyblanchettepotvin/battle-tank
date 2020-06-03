// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrackComponent.generated.h"

/**
 * TankTrackComponent implements the behavior of a tank track.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrackComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UTankTrackComponent();

protected:
	// Properties
	/** Max force in newtons output by the track. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Track)
		float MaxDrivingForce = 400000.0f; // Assume that the tank is 40 tons and acceleration is 1 g (9.81 m/s2)

	float Throttle = 0.0f;

	// Functions
	// ~ Start UStaticMeshComponent Interface
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// ~ End UStaticMeshComponent Interface

	// Getters/setters
	/** Setter for Throlle */
	UFUNCTION(BlueprintCallable, Category = Track)
		void SetThrottle(float Value);

private:
	/**
	 * Apply a force in the forward/backward direction of the track. 
	 * This simulates the track rolling and pulling/pushing the tank forward/backward. 
	 * A Throttle of -1 means the track is pushing the tank backward. 
	 * A Throttle of 1 means the track is pulling the tank forward.
	 */
	void ApplyDrivingForce();

	/**
	 * Apply a force in the opposite direction of the track's velocity. 
	 * This simulates sideway friction and prevent the tank from drifting.
	 */
	void ApplySidewayForce();

protected:
	// Delegates
	/**
	 * Delegate for OnComponentHit.
	 * @see UPrimitiveComponent
	 */
	UFUNCTION()
		virtual void OnComponentHitDelegate(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
