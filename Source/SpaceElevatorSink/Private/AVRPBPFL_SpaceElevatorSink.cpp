#include "AVRPBPFL_SpaceElevatorSink.h"

bool UAVRPBPFL_SpaceElevatorSink::BuildableIsDismantled(AFGBuildable* buildable)
{
	return buildable->GetIsDismantled();
}
