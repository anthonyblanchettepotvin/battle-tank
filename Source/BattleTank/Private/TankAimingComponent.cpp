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

	UE_LOG(LogTemp, Warning, TEXT("%s - AimAt - bSolutionFound = %s"), *GetOwner()->GetName(), bSolutionFound ? TEXT("true") : TEXT("false"));
	if (bSolutionFound) {
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
	// Get the intended aim direction
	// Get the current aim direction
	// Lerp between the current aim direction and the intended aim direction to give the new aim direction
	// Multiply the result by the barrel move speed
	// Convert the new aim direction into the new barrel rotation
	// Set the new barrel rotation

	auto BarrelRotation = BarrelComponentReference->GetForwardVector().Rotation();
	auto AimRotation = AimDirection.Rotation();
	auto DeltaRotation = AimRotation - BarrelRotation;

	BarrelComponentReference->Elevate(5);
}

void UTankAimingComponent::SetBarrelComponentReference(UTankBarrelComponent* Value)
{
	BarrelComponentReference = Value;
}
