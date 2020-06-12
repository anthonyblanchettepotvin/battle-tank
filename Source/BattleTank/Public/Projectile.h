// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

// Forward declarations
class UParticleSystemComponent;
class UProjectileMovementComponent;
class URadialForceComponent;
class UStaticMeshComponent;

/** 
 * Projectile is an Actor that implements the basic behavior of a projectile.
 * @see AActor
 */
UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
	// Constructors
public:	
	/** Default constructor for AProjectile. */
	AProjectile();

	// Components
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = true))
		UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* ProjectileMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = true))
		UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = true))
		UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = true))
		URadialForceComponent* ExplosionForce = nullptr;

	// Properties
private:
	/** The number of seconds, after the impact, before the projectile is destroyed. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = true))
		float DestroyDelay = 15.0f;

	/** The amount of damage that the projectile does on impact. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = true))
		float ProjectileDamage = 20.0f;

	// ~ Start AActor Interface
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	// ~ End AActor Interface

	// Functions
public:
	/**
	 * Launch the projectile.
	 * @param Speed The initial speed of the projectile at launch
	 */
	UFUNCTION(BlueprintCallable, Category = "Projectile")
		virtual void Launch(const float Speed);

	/** Destroy the projectile. */
	UFUNCTION(BlueprintCallable, Category = "Projectile")
		virtual void DestroyProjectile();

private:
	/**
	 * Handle OnComponentHit broadcast from ProjectileMesh.
	 * @see UPrimitiveComponent
	 */
	UFUNCTION()
		void HandleCollisionMeshOnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
