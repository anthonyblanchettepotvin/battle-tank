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

void AMortarAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AMortar* ControlledMortar = GetControlledMortar();
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ControlledMortar || !PlayerPawn) { return; }

	FVector AimLocation = PlayerPawn->GetActorLocation() + AimLocationOffset;
	ControlledMortar->AimAtLocation(AimLocation);

	if (ControlledMortar->GetAimingState() == ETankAimingState::Locked)
	{
		ControlledMortar->Fire();
	}
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

			AttachToPawn(ControlledMortar);
		}
	}
}

void AMortarAIController::HandleOnMortarDeath()
{
	DetachFromPawn();
	UnPossess();
}

AMortar* AMortarAIController::GetControlledMortar() const
{
	return Cast<AMortar>(GetPawn());
}
