// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrelComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
		UTankBarrelComponent* BarrelComponentReference = nullptr;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * Tell the component to make the tank aim at a location.
	 * @param Location The location at which the tank should aim
	 * @param InitialProjectileVelocity The initial velocity at which a projectile is fired
	 */
	virtual void AimAt(FVector Location, float InitialProjectileVelocity);

	virtual void MoveBarrelTowards(FVector AimDirection);

	// Getters/setters
	void SetBarrelComponentReference(UTankBarrelComponent* Value);
};
