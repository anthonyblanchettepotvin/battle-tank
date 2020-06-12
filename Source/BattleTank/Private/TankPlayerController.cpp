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

	OnBeginPlayEnd();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
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

			AttachToPawn(ControlledTank);
		}
	}
}

void ATankPlayerController::AimTowardsCrosshair()
{
	ATank* ControlledTank = GetControlledTank();

	if (!ControlledTank) { return; }
	
	FVector AimLocation;

	if (CrosshairToWorldLocation(AimLocation))
	{
		ControlledTank->AimAtLocation(AimLocation);
	}
}

bool ATankPlayerController::CrosshairToWorldLocation(FVector& OutLocation) const
{
	int32 ViewportX, ViewportY;
	GetViewportSize(ViewportX, ViewportY);
	FVector2D ScreenPosition = { ViewportX * CrosshairPosition.X, ViewportY * CrosshairPosition.Y };

	bool bHitFound;
	FHitResult HitResult;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetPawn());
	CollisionQueryParams.bTraceComplex = true;

	bHitFound = GetHitResultAtScreenPosition(
		ScreenPosition,
		ECC_Visibility,
		CollisionQueryParams,
		HitResult
	);

	if (bHitFound) { OutLocation = HitResult.ImpactPoint; }

	return bHitFound;
}

void ATankPlayerController::HandleTankOnDeath()
{
	DetachFromPawn();
	UnPossess();
	StartSpectatingOnly();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
