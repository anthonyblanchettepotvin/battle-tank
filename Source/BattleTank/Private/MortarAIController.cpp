// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "MortarAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Mortar.h"
#include "TankAimingComponent.h"
#include "HealthComponent.h"

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
			UHealthComponent* HealthComponent = PossessedMortar->GetHealthComponent();
			if (HealthComponent)
			{
				HealthComponent->OnDeath.AddUniqueDynamic(this, &AMortarAIController::HandleOnDeath);
			}
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

void AMortarAIController::HandleOnDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("%s - HandleOnDeath - Mortar died"), *GetName());

	bMortarIsDead = true;

	DetachFromPawn();
}
