// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "DrawDebugHelpers.h"

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

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	
	FVector AimLocation;

	if (GetCrosshairAimLocation(AimLocation))
	{
		QUICK_LOG_WARN("AimLocation = %s", *AimLocation.ToString())

		DrawDebugSphere(GetWorld(), AimLocation, 10, 16, FColor::Red);
	}
}

bool ATankPlayerController::GetCrosshairAimLocation(FVector& OutAimLocation) const
{
	int32 ViewportX, ViewportY;
	GetViewportSize(ViewportX, ViewportY);
	FVector2D ScreenPosition = { ViewportX * CrosshairPosition.X, ViewportY * CrosshairPosition.Y };

	bool bHit;
	FHitResult Hit;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetControlledTank());
	Params.bTraceComplex = true;

	bHit = GetHitResultAtScreenPosition(ScreenPosition, ECC_Visibility, Params, Hit);

	if (bHit) { OutAimLocation = Hit.ImpactPoint; }

	return bHit;
}
