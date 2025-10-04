#pragma once

#include "CoreMinimal.h"
#include "FGBuildable.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AVRPBPFL_SpaceElevatorSink.generated.h"

/**
 * Helper to expose some Buildable properties to blueprints
 */
UCLASS()
class SPACEELEVATORSINK_API UAVRPBPFL_SpaceElevatorSink : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static bool BuildableIsDismantled(AFGBuildable* buildable);
};
