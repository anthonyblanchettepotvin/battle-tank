// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"

ATankAIController::ATankAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank* ControlledTank = GetControlledTank();
		if (ControlledTank)
		{
			ControlledTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::HandleOnTankDeath);
		}
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTankIsDead) { return; }

	ATank* ControlledTank = GetControlledTank();
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ControlledTank || !PlayerPawn) { return; }

	MoveToActor(PlayerPawn, AcceptanceRadius);

	FVector AimLocation = PlayerPawn->GetActorLocation() + FVector(0.0f, 0.0f, 100.0f);
	ControlledTank->AimAtLocation(AimLocation);

	if (ControlledTank->GetAimingState() == ETankAimingState::Locked)
	{
		ControlledTank->Fire();
	}
}

void ATankAIController::HandleOnTankDeath()
{
	bTankIsDead = true;

	DetachFromPawn();
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
