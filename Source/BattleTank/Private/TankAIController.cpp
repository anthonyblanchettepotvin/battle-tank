// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankAimingComponent.h"

ATankAIController::ATankAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	if (ensure(GetPawn()))
	{
		AimingComponentRef = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(AimingComponentRef && PlayerTank)) { return; }

	MoveToActor(PlayerTank, AcceptanceRadius);

	AimingComponentRef->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponentRef->GetState() == ETankAimingState::Locked)
	{
		AimingComponentRef->Fire();
	}
}
