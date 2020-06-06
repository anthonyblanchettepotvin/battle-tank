// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawnPoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	/** Default constructor for USpawnPoint. */
	USpawnPoint();

	// Properties
	/** The Actor to spawn. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SpawnPoint")
		TSubclassOf<AActor> ActorToSpawn = nullptr;

	// Functions
protected:
	// ~ Start USceneComponent Interface
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// ~ End USceneComponent Interface
};
