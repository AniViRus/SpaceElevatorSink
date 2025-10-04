#pragma once

#include "CoreMinimal.h"
#include "FGBuildableSpaceElevator.h"
#include "Subsystem/ModSubsystem.h"
#include "FGResourceSinkSubsystem.h"
#include "AVRPSpaceElevatorSinkSubsystem.generated.h"

/**
 * Subsystem which stores Resource Sink subsystem and modifies behaviour of Space Elevator to make it sink wrong items at inputs
 */
UCLASS()
class SPACEELEVATORSINK_API AAVRPSpaceElevatorSinkSubsystem : public AModSubsystem
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;
protected:
	bool hooksInitialized = false;
	FDelegateHandle hookHandler;
	UFUNCTION(BlueprintImplementableEvent)
	bool ResourceSinkSchematicUnlocked();
	UPROPERTY()
	AFGResourceSinkSubsystem* mCachedResourceSinkSubsystem;
};
