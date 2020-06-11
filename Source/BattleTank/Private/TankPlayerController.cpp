// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"

ATankPlayerController::ATankPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AfterBeginPlay();
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank* ControlledTank = GetControlledTank();
		if (ControlledTank)
		{
			ControlledTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::HandleTankOnDeath);
		}
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTankIsDead) { return; }

	AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair()
{
	ATank* ControlledTank = GetControlledTank();

	if (!ControlledTank) { return; }
	
	FVector AimLocation;

	if (GetCrosshairAimLocation(AimLocation))
	{
		ControlledTank->AimAtLocation(AimLocation);
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

void ATankPlayerController::HandleTankOnDeath()
{
	bTankIsDead = true;

	DetachFromPawn();
	StartSpectatingOnly();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
