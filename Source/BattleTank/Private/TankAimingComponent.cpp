// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "TankBarrelComponent.h"
#include "TankTurretComponent.h"
#include "TankAimingComponent.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankAimingComponent::AimAt(FVector Location, float InitialProjectileVelocity)
{
	if (!BarrelRef || !TurretRef) { return; }
	
	FVector LaunchVelocity = { 0.0f, 0.0f, 0.0f };
	FVector StartLocation = BarrelRef->GetSocketLocation(FName("Muzzle"));

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());

	bool bSolutionFound = UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		StartLocation,
		Location,
		InitialProjectileVelocity,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,
		ActorsToIgnore,
		false
	);

	if (bSolutionFound)
	{
		FVector AimDirection = LaunchVelocity.GetSafeNormal();

		UE_LOG(LogTemp, Warning, TEXT("%s - AimAt - Aim direction found = %s"), *GetOwner()->GetName(), *AimDirection.ToString());

		MoveToAimTowards(AimDirection);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s - AimAt - Aim direction not found"), *GetOwner()->GetName());
	}
}

void UTankAimingComponent::MoveToAimTowards(FVector AimDirection)
{
	auto BarrelRotation = BarrelRef->GetForwardVector().Rotation();
	auto AimRotation = AimDirection.Rotation();
	auto DeltaRotation = AimRotation - BarrelRotation;

	BarrelRef->Elevate(DeltaRotation.Pitch);
	TurretRef->Rotate(DeltaRotation.Yaw);
}

void UTankAimingComponent::SetBarrelComponentReference(UTankBarrelComponent* Value)
{
	BarrelRef = Value;
}

void UTankAimingComponent::SetTurretComponentReference(UTankTurretComponent* Value)
{
	TurretRef = Value;
}
