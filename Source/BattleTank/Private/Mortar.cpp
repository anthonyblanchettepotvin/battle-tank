// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "Mortar.h"
#include "HealthComponent.h"
#include "TankAimingComponent.h"

AMortar::AMortar()
{
	PrimaryActorTick.bCanEverTick = false;

	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(FName("HealthComponent"));
}

void AMortar::BeginPlay()
{
	Super::BeginPlay();

	if (HealthComponent)
	{
		HealthComponent->OnDeath.AddUniqueDynamic(this, &AMortar::HandleHealthComponentOnDeath);
	}
}

void AMortar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMortar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AMortar::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!HealthComponent) { return 0.0f; }

	return HealthComponent->ApplyDamage(DamageAmount);
}

void AMortar::HandleHealthComponentOnDeath()
{
	if (OnDeath.IsBound())
	{
		OnDeath.Broadcast();
	}
}

void AMortar::AimAtLocation(const FVector TargetLocation)
{
	AimingComponent->AimAtLocation(TargetLocation);
}

void AMortar::Fire()
{
	AimingComponent->Fire();
}

ETankAimingState AMortar::GetAimingState() const
{
	return AimingComponent->GetState();
}

UTankAimingComponent* AMortar::GetAimingComponent() const
{
	return AimingComponent;
}

UHealthComponent* AMortar::GetHealthComponent() const
{
	return HealthComponent;
}
