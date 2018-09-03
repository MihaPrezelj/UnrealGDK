#pragma once

#include "SpatialReceiver.h"
#include "EngineClasses/SpatialNetBitReader.h"

class ComponentReader
{
public:
	ComponentReader(class USpatialNetDriver* InNetDriver, FObjectReferencesMap& InObjectReferencesMap, TSet<UnrealObjectRef>& InUnresolvedRefs);

	void ApplyComponentData(const Worker_ComponentData& ComponentData, UObject* Object, USpatialActorChannel* Channel);
	void ApplyComponentUpdate(const Worker_ComponentUpdate& ComponentUpdate, UObject* Object, USpatialActorChannel* Channel);

private:
	void ApplySchemaObject(Schema_Object* ComponentObject, UObject* Object, USpatialActorChannel* Channel, bool bIsInitialData, TArray<Schema_FieldId>* ClearedIds = nullptr);
	void ApplyProperty(Schema_Object* Object, Schema_FieldId Id, std::uint32_t Index, UProperty* Property, uint8* Data, int32 Offset, uint16 ParentIndex);
	void ApplyArray(Schema_Object* Object, Schema_FieldId Id, UArrayProperty* Property, uint8* Data, int32 Offset, uint16 ParentIndex);

	void ReadStructProperty(FSpatialNetBitReader& Reader, UStructProperty* Property, uint8* Data, bool& bOutHasUnmapped);
	std::uint32_t GetPropertyCount(const Schema_Object* Object, Schema_FieldId Id, UProperty* Property);

private:
	class USpatialPackageMapClient* PackageMap;
	class UNetDriver* NetDriver;
	FObjectReferencesMap& ObjectReferencesMap;
	TSet<UnrealObjectRef>& UnresolvedRefs;
};