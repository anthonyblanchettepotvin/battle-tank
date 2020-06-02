// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	/** Default constructor for ATank. */
	ATank();

private:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Tank, meta = (AllowPrivateAccess = true))
		UTankAimingComponent* AimingComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Tank, meta = (AllowPrivateAccess = true))
		UTankMovementComponent* MovementComponent = nullptr;

	// Functions
	// ~ Begin APawn Interface
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// ~ End APawn Interface
};
