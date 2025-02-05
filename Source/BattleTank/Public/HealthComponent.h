// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);

/** 
 * HealthComponent is a component used to manage an Actor's health.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	// Constructors
public:
	/** Default constructor for UHealthComponent. */
	UHealthComponent();

	// Properties
private:
	/** The maximum amount of health. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = GetMaxHealth, Category = "Health", meta = (AllowPrivateAccess = true))
		float MaxHealth = 100.0f;

	/** The current amount of health. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = GetCurrentHealth, Category = "Health", meta = (AllowPrivateAccess = true))
		float CurrentHealth = 0.0f;

	// ~ Start UActorComponent Interface
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// ~ End UActorComponent Interface

	// Functions
public:
	/**
	 * Calculate the amount of damage to do and apply it.
	 * @param RawDamage The raw amount of damage to be done
	 * @return The actual amount of damage done
	 */
	UFUNCTION(BlueprintCallable, Category = "Health")
		virtual float ApplyDamage(const float RawDamage);

	// Getter/setters
public:
	/** Getter for MaxHealth */
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetMaxHealth() const;

	/** Getter for CurrentHealth */
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetCurrentHealth() const;

	/** Getter for HealthPercentage */
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercentage() const;

	/** Getter for IsDead */
	UFUNCTION(BlueprintPure, Category = "Health")
		bool IsDead() const;

	// Delegates
public:
	/** Called when the owner has died. */
	UPROPERTY(BlueprintAssignable, Category = "Health")
		FOnDeathSignature OnDeath;
};
