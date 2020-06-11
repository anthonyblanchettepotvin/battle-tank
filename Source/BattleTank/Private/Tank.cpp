// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#include "Tank.h"
#include "HealthComponent.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;

	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
	MovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("MovementComponent"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(FName("HealthComponent"));
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	if (HealthComponent)
	{
		HealthComponent->OnDeath.AddUniqueDynamic(this, &ATank::HandleHealthComponentOnDeath);
	}
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
	const float MinDamage = 0.0f;

	if (!HealthComponent) { return MinDamage; }

	return HealthComponent->ApplyDamage(DamageAmount);
}

void ATank::AimAtLocation(FVector TargetLocation)
{
	AimingComponent->AimAtLocation(TargetLocation);
}

void ATank::Fire()
{
	AimingComponent->Fire();
}

void ATank::HandleHealthComponentOnDeath()
{
	if (OnDeath.IsBound())
	{
		OnDeath.Broadcast();
	}
}

ETankAimingState ATank::GetAimingState() const
{
	return AimingComponent->GetState();
}

UTankAimingComponent* ATank::GetAimingComponent() const
{
	return AimingComponent;
}

UHealthComponent* ATank::GetHealthComponent() const
{
	return HealthComponent;
}
