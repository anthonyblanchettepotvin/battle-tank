// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
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

ATankAIController::ATankAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* ControlledTank = GetControlledTank();
	ATank* PlayerTank = GetPlayerTank();

	if (!ControlledTank ||
		!PlayerTank) { return; }

	ControlledTank->AimAt(PlayerTank->GetActorLocation());

	ControlledTank->Fire(); // TODO: Don't fire every frame
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
