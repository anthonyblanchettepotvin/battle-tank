// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	// Properties
	/** The maximum amount of health. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float MaxHealth = 100.0f;

	/** The current amount of health. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float CurrentHealth = 0.0f;

	// Functions
protected:
	// ~ Start UActorComponent Interface
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// ~ End UActorComponent Interface

	/**
	 * Calculate the amount of damage to do and apply it.
	 * @param RawDamage The raw amount of damage to be done
	 * @return The actual amount of damage done
	 */
	UFUNCTION(BlueprintCallable, Category = "Health")
		virtual float ApplyDamage(float RawDamage);

	// Getter/setters
	/** Getter for HealthPercentage */
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercentage() const;

	/** Getter for IsDead */
	UFUNCTION(BlueprintPure, Category = "Health")
		bool IsDead() const;

	// Delegates
	/** Called when the owner has died. */
	UPROPERTY(BlueprintAssignable, Category = "Health")
		FOnDeathSignature OnDeath;
};
