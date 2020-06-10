// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "MortarAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Mortar.h"
#include "TankAimingStateEnum.h"

AMortarAIController::AMortarAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMortarAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AMortarAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		AMortar* ControlledMortar = GetControlledMortar();
		if (ControlledMortar)
		{
			ControlledMortar->OnDeath.AddUniqueDynamic(this, &AMortarAIController::HandleOnMortarDeath);
		}
	}
}

void AMortarAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bMortarIsDead) { return; }

	AMortar* ControlledMortar = GetControlledMortar();
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ControlledMortar || !PlayerPawn) { return; }

	FVector AimLocation = PlayerPawn->GetActorLocation() + FVector(0.0f, 0.0f, 100.0f);
	ControlledMortar->AimAt(AimLocation);

	if (ControlledMortar->GetAimingState() == ETankAimingState::Locked)
	{
		ControlledMortar->Fire();
	}
}

void AMortarAIController::HandleOnMortarDeath()
{
	bMortarIsDead = true;

	DetachFromPawn();
}

AMortar* AMortarAIController::GetControlledMortar() const
{
	return Cast<AMortar>(GetPawn());
}
