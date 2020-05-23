// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

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

void ATankPlayerController::BeginPlay()
{
	auto ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		QUICK_LOG_WARN("GetControlledTank = %s", *GetControlledTank()->GetName())
	}
	else
	{
		QUICK_LOG_ERROR("Possessed pawn is not Tank")
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
