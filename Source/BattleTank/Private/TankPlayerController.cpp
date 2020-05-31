// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#include "TankPlayerController.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetControlledTank()) { return; }

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
		GetControlledTank()->AimAt(AimLocation);
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
