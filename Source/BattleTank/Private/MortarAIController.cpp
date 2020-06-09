// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "MortarAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Mortar.h"
#include "TankAimingComponent.h"

AMortarAIController::AMortarAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMortarAIController::BeginPlay()
{
	Super::BeginPlay();

	if (ensure(GetPawn()))
	{
		AimingComponentRef = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	}
}

void AMortarAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		AMortar* PossessedMortar = Cast<AMortar>(InPawn);
		if (PossessedMortar)
		{
			PossessedMortar->OnDeath.AddUniqueDynamic(this, &AMortarAIController::HandleOnMortarDeath);
		}
	}
}

void AMortarAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawnRef = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (bMortarIsDead) { return; }
	if (!ensure(AimingComponentRef && PlayerPawnRef)) { return; }

	FVector AimLocation = PlayerPawnRef->GetActorLocation() + FVector(0.0f, 0.0f, 100.0f);
	AimingComponentRef->AimAt(AimLocation);

	if (AimingComponentRef->GetState() == ETankAimingState::Locked)
	{
		AimingComponentRef->Fire();
	}
}

void AMortarAIController::HandleOnMortarDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("%s - HandleOnMortarDeath - Mortar died"), *GetName());

	bMortarIsDead = true;

	DetachFromPawn();
}
