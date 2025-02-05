// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawnPoint.generated.h"

/** 
 * SpawnPoint is used to spawn an Actor and attach it's root component to this component.
 * @see AActor
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

	// Constructors
public:	
	/** Default constructor for USpawnPoint. */
	USpawnPoint();

	// Properties
private:
	/** The Actor to spawn. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SpawnPoint", meta = (AllowPrivateAccess = true))
		TSubclassOf<AActor> ActorToSpawn = nullptr;

	/** The spawned Actor. */
	UPROPERTY(BlueprintGetter = GetSpawnedActor, Category = "SpawnPoint")
		AActor* SpawnedActor = nullptr;

	// ~ Start USceneComponent Interface
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// ~ End USceneComponent Interface

	// Getters/setters
public:
	/** Getter for SpawnedActor */
	UFUNCTION(BlueprintPure, Category = "SpawnPoint")
		AActor* GetSpawnedActor() const;
};
