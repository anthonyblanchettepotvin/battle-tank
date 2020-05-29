// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.h"
#include "TankBarrelComponent.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
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
	if (!BarrelComponentReference) { return; }
	
	FVector LaunchVelocity = { 0.0f, 0.0f, 0.0f };
	FVector StartLocation = BarrelComponentReference->GetSocketLocation(FName("Muzzle"));

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

		MoveBarrelTowards(AimDirection);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s - AimAt - Aim direction not found"), *GetOwner()->GetName());
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	auto BarrelRotation = BarrelComponentReference->GetForwardVector().Rotation();
	auto AimRotation = AimDirection.Rotation();
	auto DeltaRotation = AimRotation - BarrelRotation;

	BarrelComponentReference->Elevate(DeltaRotation.Pitch);
}

void UTankAimingComponent::SetBarrelComponentReference(UTankBarrelComponent* Value)
{
	BarrelComponentReference = Value;
}

void UTankAimingComponent::SetTurretComponentReference(UTankTurretComponent* Value)
{
	TurretComponentReference = Value;
}
