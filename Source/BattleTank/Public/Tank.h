// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrelComponent;
class UTankTurretComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Tank, meta = (AllowPrivateAccess = true))
		UTankAimingComponent* AimingComponent = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**
	 * Make the tank aim at a location.
	 * @param Location The location at which the tank should aim
	 */
	virtual void AimAt(FVector Location);

	// Setters/getters
	UFUNCTION(BlueprintCallable, Category = Tank)
		void SetBarrelComponentReference(UTankBarrelComponent* Value);

	UFUNCTION(BlueprintCallable, Category = Tank)
		void SetTurretComponentReference(UTankTurretComponent* value);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank | Firing")
		float InitialProjectileVelocity = 10000; // 100cm/s * 100 m/s = 10000 cm/s = 100 m/s
};
