// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;
class URadialForceComponent;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = true))
		UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = true))
		UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = true))
		URadialForceComponent* ExplosionForce = nullptr;

	// Properties
	/** The number of seconds, after the impact, before the projectile is destroyed. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Projectile)
		float DestroyDelay = 15.0f;

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

private:
	/** Destroy the projectile. */
	void DestroyProjectile();

protected:
	// Delegates
	/**
	 * Delegate for OnComponentHit.
	 * @see UPrimitiveComponent
	 */
	UFUNCTION()
		virtual void OnComponentHitDelegate(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
