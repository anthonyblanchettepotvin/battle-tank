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

	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		StartLocation,
		Location,
		InitialProjectileVelocity,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::TraceFullPath,
		FCollisionResponseParams::DefaultResponseParam,
		ActorsToIgnore,
		true))
	{
		FVector AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *GetOwner()->GetName(), *AimDirection.ToString())
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
