// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#include "TankPlayerController.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ensure(GetPawn()))
	{
		AimingComponentRef = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	}

	AfterBeginPlay();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(AimingComponentRef)) { return; }
	
	FVector AimLocation;

	if (GetCrosshairAimLocation(AimLocation))
	{
		AimingComponentRef->AimAt(AimLocation);
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
	Params.AddIgnoredActor(GetPawn());
	Params.bTraceComplex = true;

	bHit = GetHitResultAtScreenPosition(ScreenPosition, ECC_Visibility, Params, Hit);

	if (bHit) { OutAimLocation = Hit.ImpactPoint; }

	return bHit;
}
