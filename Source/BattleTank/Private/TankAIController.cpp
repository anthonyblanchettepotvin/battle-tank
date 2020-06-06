// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "HealthComponent.h"

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
			UHealthComponent* HealthComponent = PossessedTank->GetHealthComponent();
			if (HealthComponent)
			{
				HealthComponent->OnDeath.AddUniqueDynamic(this, &ATankAIController::HandleOnDeath);
			}
		}
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawnRef = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (bTankIsDead) { return; }
	if (!ensure(AimingComponentRef && PlayerPawnRef)) { return; }

	MoveToActor(PlayerPawnRef, AcceptanceRadius);

	FVector AimLocation = PlayerPawnRef->GetActorLocation() + FVector(0.0f, 0.0f, 100.0f);
	AimingComponentRef->AimAt(AimLocation);

	if (AimingComponentRef->GetState() == ETankAimingState::Locked)
	{
		AimingComponentRef->Fire();
	}
}

void ATankAIController::HandleOnDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("%s - HandleOnDeath - Tank died"), *GetName());

	bTankIsDead = true;

	DetachFromPawn();
}
