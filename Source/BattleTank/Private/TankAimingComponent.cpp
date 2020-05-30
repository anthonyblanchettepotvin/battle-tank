// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
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

void UTankAimingComponent::AimAt(FVector Location, float InitialProjectileSpeed)
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
		InitialProjectileSpeed,
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

		DrawDebugDirectionalArrow(GetWorld(), StartLocation, StartLocation + (AimDirection * 1000.0f), 20.0f, FColor::Red, false, -1.0f, 0, 10.0f);

		//UE_LOG(LogTemp, Warning, TEXT("%s - AimAt - Aim direction found = %s"), *GetOwner()->GetName(), *AimDirection.ToString());

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

	BarrelRef->Elevate(AimDirection);
	TurretRef->Rotate(AimDirection);
}

void UTankAimingComponent::SetBarrelComponentReference(UTankBarrelComponent* Value)
{
	BarrelRef = Value;
}

void UTankAimingComponent::SetTurretComponentReference(UTankTurretComponent* Value)
{
	TurretRef = Value;
}
