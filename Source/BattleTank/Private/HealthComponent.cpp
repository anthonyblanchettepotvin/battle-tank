// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

float UHealthComponent::ApplyDamage(float RawDamage)
{
	float DamageApplied = 0.0f;

	if (!IsDead())
	{
		DamageApplied = FMath::Clamp<float>(RawDamage, 0.0f, CurrentHealth);
		CurrentHealth -= DamageApplied;

		if (IsDead())
		{
			if (OnDeath.IsBound())
			{
				OnDeath.Broadcast();
			}
		}
	}

	return DamageApplied;
}

float UHealthComponent::GetHealthPercentage() const
{
	return CurrentHealth / MaxHealth;
}

bool UHealthComponent::IsDead() const
{
	return CurrentHealth <= 0.0f;
}
