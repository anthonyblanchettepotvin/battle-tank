// Copyright © 2020 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "TankAimingStateEnum.generated.h"

/**
 * Enum indicating different state of the TankAimingComponent.
 * @see UTankAimingComponent
 */
UENUM()
enum class ETankAimingState : uint8
{
    Reloading,
    Aiming,
    Locked,
    OutOfAmmo
};
