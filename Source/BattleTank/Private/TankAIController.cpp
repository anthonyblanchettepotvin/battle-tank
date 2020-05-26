// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

#define QUICK_LOG_WARN(Format, ...) \
{ \
	FString Message = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(LogTemp, Warning, \
		TEXT("%s - %s"), \
		TEXT(__FUNCTION__), \
		*Message) \
}

#define QUICK_LOG_ERROR(Format, ...) \
{ \
	FString Message = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(LogTemp, Error, \
		TEXT("%s - %s"), \
		TEXT(__FUNCTION__), \
		*Message) \
}

void ATankAIController::BeginPlay()
{
	auto ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		QUICK_LOG_WARN("GetControlledTank = %s", *GetControlledTank()->GetName())
	}
	else
	{
		QUICK_LOG_ERROR("Possessed pawn is not Tank or null")
	}

	auto PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		QUICK_LOG_WARN("GetPlayerTank = %s", *GetPlayerTank()->GetName())
	}
	else
	{
		QUICK_LOG_ERROR("Player pawn is not Tank or null")
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetControlledTank() ||
		!GetPlayerTank()) { return; }

	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
