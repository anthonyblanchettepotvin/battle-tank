// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	/** Default constructor for AProjectile. */
	AProjectile();

private:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = true))
		UProjectileMovementComponent* ProjectileMovement = nullptr;

	// Functions
	// ~ Start AActor Interface
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	// ~ End AActor Interface

	/**
	 * Launch the projectile.
	 * @param Speed The initial speed of the projectile at launch
	 */
	virtual void Launch(float Speed);
};
