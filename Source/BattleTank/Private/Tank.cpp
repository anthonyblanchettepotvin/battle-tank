// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#include "Tank.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;

	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
	MovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("MovementComponent"));
}

float ATank::GetHealthPercentage() const
{
	return CurrentHealth / MaxHealth;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = FMath::Clamp<float>(DamageAmount, 0.0f, CurrentHealth);
	CurrentHealth -= DamageApplied;

	if (CurrentHealth <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s - TakeDamage - Tank is dead"), *GetName());
	}

	return DamageApplied;
}
