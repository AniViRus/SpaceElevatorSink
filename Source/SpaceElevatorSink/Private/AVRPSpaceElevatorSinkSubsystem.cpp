#include "AVRPSpaceElevatorSinkSubsystem.h"
#include "SpaceElevatorSink.h"
#include "Logging/StructuredLog.h"
#include "FGInventoryComponent.h"
#include "SubsystemActorManager.h"
#include "Patching/NativeHookManager.h"
#include "FGFactoryConnectionComponent.h"

void AAVRPSpaceElevatorSinkSubsystem::BeginPlay()
{
	Super::BeginPlay();
	if (hooksInitialized) return;
	mCachedResourceSinkSubsystem = AFGResourceSinkSubsystem::Get(this);
	//Hooking
	AFGBuildableSpaceElevator* SpaceElevator = GetMutableDefault<AFGBuildableSpaceElevator>();
	hookHandler = SUBSCRIBE_METHOD_VIRTUAL_AFTER(AFGBuildableSpaceElevator::Factory_Tick, SpaceElevator, [this](AFGBuildableSpaceElevator* self, float dt)
		{
			if (!HasAuthority() || !ResourceSinkSchematicUnlocked()) return;
			
			TArray<FInventoryItem> items;
			self->ForEachComponent<UFGFactoryConnectionComponent>(true, [&](UFGFactoryConnectionComponent* FactoryConn) {
				if (FactoryConn->IsConnected() && FactoryConn->Factory_PeekOutput(items)) {
					while (!items.IsEmpty()) {
						
						if (mCachedResourceSinkSubsystem->AddPoints_ThreadSafe(items[0].GetItemClass())) {
							float offset;
							FInventoryItem item;
							FactoryConn->Factory_GrabOutput(item, offset);
							items.RemoveAt(0);
							//UE_LOGFMT(LogSpaceElevatorSink, Verbose, "Item: {Name}", item.GetItemClass().GetDefaultObject()->mDisplayName.ToString());
						}
						else break;
					}
				}
				});
		});
	//~Hooking
	hooksInitialized = true;
}

void AAVRPSpaceElevatorSinkSubsystem::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	if (hookHandler.IsValid()) UNSUBSCRIBE_METHOD(AFGBuildableSpaceElevator::Factory_Tick, hookHandler);
}