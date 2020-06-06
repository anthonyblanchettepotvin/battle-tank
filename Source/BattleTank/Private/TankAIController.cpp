// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
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

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (PossessedTank)
		{
			PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::HandleOnDeath);
		}
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(AimingComponentRef && PlayerTank)) { return; }

	MoveToActor(PlayerTank, AcceptanceRadius);

	FVector AimLocation = PlayerTank->GetActorLocation() + FVector(0.0f, 0.0f, 100.0f);
	AimingComponentRef->AimAt(AimLocation);

	if (AimingComponentRef->GetState() == ETankAimingState::Locked)
	{
		AimingComponentRef->Fire();
	}
}

void ATankAIController::HandleOnDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("%s - HandleOnDeath - Tank died"), *GetName());
}
