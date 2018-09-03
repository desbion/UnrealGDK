//// Copyright (c) Improbable Worlds Ltd, All Rights Reserved
//
//#pragma once
//
//#include "CoreMinimal.h"
//
//#include "SpatialReceiver.h"
//#include "SpatialNetDriver.h"
//
//#include "improbable/c_worker.h"
//#include "improbable/c_schema.h"
//
//#include "SchemaHelpers.h"
//#include "SpatialReceiver.h"
//
//#include "SpatialInterop.generated.h"
//
//class USpatialActorChannel;
//
//
//
//UCLASS()
//class SPATIALGDK_API USpatialInterop : public UObject
//{
//	GENERATED_BODY()
//
//public:
//	USpatialInterop();
//
//	void Init(USpatialNetDriver* NetDriver);
//
//	void ProcessOps(Worker_OpList* OpList);
//
//	virtual void FinishDestroy() override;
//
//	FClassInfo* FindClassInfoByClass(UClass* Class);
//	void CreateTypebindings();
//
//	UObject* GetTargetObjectFromChannelAndClass(USpatialActorChannel* Channel, UClass* Class);
//
//	bool HasComponentAuthority(Worker_EntityId EntityId, Worker_ComponentId ComponentId);
//
//	void OnCommandRequest(Worker_CommandRequestOp& Op);
//	void OnCommandResponse(Worker_CommandResponseOp& Op);
//
//	void OnDynamicData(Worker_EntityId EntityId, Worker_ComponentData& Data, USpatialActorChannel* Channel, USpatialPackageMapClient* PackageMap);
//
//	void OnComponentUpdate(Worker_ComponentUpdateOp& Op);
//
//	void OnAuthorityChange(Worker_AuthorityChangeOp& Op);
//
//	void HandleComponentUpdate(const Worker_ComponentUpdate& ComponentUpdate, UObject* TargetObject, USpatialActorChannel* Channel, EReplicatedPropertyGroup PropertyGroup, bool bAutonomousProxy);
//
//	void SendReserveEntityIdRequest(USpatialActorChannel* Channel);
//
//	void AddPendingActorRequest(Worker_RequestId RequestId, USpatialActorChannel* Channel);
//	USpatialActorChannel* RemovePendingActorRequest(Worker_RequestId RequestId);
//
//	void OnReserveEntityIdResponse(Worker_ReserveEntityIdResponseOp& Op);
//
//	void OnCreateEntityResponse(Worker_CreateEntityResponseOp& Op);
//
//	Worker_RequestId SendCreateEntityRequest(USpatialActorChannel* Channel, const FVector& Location, const FString& PlayerWorkerId, const TArray<uint16>& RepChanged, const TArray<uint16>& HandoverChanged);
//
//	Worker_RequestId CreateActorEntity(const FString& ClientWorkerId, const FVector& Position, const FString& Metadata, const struct FPropertyChangeState& InitialChanges, USpatialActorChannel* Channel);
//
//	bool IsCriticalEntity(Worker_EntityId EntityId);
//
//	void DeleteEntityIfAuthoritative(Worker_EntityId EntityId);
//
//	void SendSpatialPositionUpdate(Worker_EntityId EntityId, const FVector& Location);
//
//	void SendComponentUpdates(UObject* Object, const struct FPropertyChangeState& Changes, USpatialActorChannel* Channel);
//
//	void SendRPC(UObject* TargetObject, UFunction* Function, void* Parameters, bool bOwnParameters = false);
//
//	void ResetOutgoingRepUpdate(USpatialActorChannel* DependentChannel, UObject* ReplicatedObject, int16 Handle);
//	void QueueOutgoingRepUpdate(USpatialActorChannel* DependentChannel, UObject* ReplicatedObject, int16 Handle, const TSet<const UObject*>& UnresolvedObjects);
//
//	void QueueIncomingRepUpdates(FChannelObjectPair ChannelObjectPair, const FObjectReferencesMap& ObjectReferencesMap, const TSet<UnrealObjectRef>& UnresolvedRefs);
//
//	void QueueOutgoingRPC(const UObject* UnresolvedObject, UObject* TargetObject, UFunction* Function, void* Parameters);
//
//	void ResolvePendingOperations(UObject* Object, const UnrealObjectRef& ObjectRef);
//	void ResolvePendingOperations_Internal(UObject* Object, const UnrealObjectRef& ObjectRef);
//
//	void ResolveOutgoingOperations(UObject* Object);
//	void ResolveIncomingOperations(UObject* Object, const UnrealObjectRef& ObjectRef);
//
//	void ResolveOutgoingRPCs(UObject* Object);
//
//	void AddActorChannel(const Worker_EntityId& EntityId, USpatialActorChannel* Channel);
//	USpatialActorChannel* GetActorChannelByEntityId(const Worker_EntityId& EntityId) const;
//
//	Worker_Connection* Connection;
//	USpatialNetDriver* NetDriver;
//
//	using FUnresolvedEntry = TSharedPtr<TSet<const UObject*>>;
//	using FHandleToUnresolved = TMap<uint16, FUnresolvedEntry>;
//	using FChannelToHandleToUnresolved = TMap<FChannelObjectPair, FHandleToUnresolved>;
//	using FOutgoingRepUpdates = TMap<const UObject*, FChannelToHandleToUnresolved>;
//
//	FChannelToHandleToUnresolved PropertyToUnresolved;
//	FOutgoingRepUpdates ObjectToUnresolved;
//
//	// TODO: Figure out how to remove entries when Channel/Actor gets deleted
//	TMap<UnrealObjectRef, TSet<FChannelObjectPair>> IncomingRefsMap;
//	TMap<FChannelObjectPair, FObjectReferencesMap> UnresolvedRefsMap;
//
//	TMap<Worker_EntityId, USpatialActorChannel*> EntityToActorChannel;
//
//	struct FPendingRPCParams
//	{
//		FPendingRPCParams(UObject* InTargetObject, UFunction* InFunction, void* InParameters)
//			: TargetObject(InTargetObject), Function(InFunction), Parameters(InParameters) {}
//
//		UObject* TargetObject;
//		UFunction* Function;
//		void* Parameters;
//	};
//	using FOutgoingRPCMap = TMap<const UObject*, TArray<FPendingRPCParams>>;
//
//	FOutgoingRPCMap OutgoingRPCs;
//
//	TArray<TPair<UObject*, UnrealObjectRef>> ResolvedObjectQueue;
//
//	TArray<UClass*> DTBClasses;
//	TMap<UClass*, FClassInfo> ClassInfoMap;
//	TMap<Worker_ComponentId, UClass*> ComponentToClassMap;
//
//	TMap<Worker_EntityId, TMap<Worker_ComponentId, Worker_Authority>> ComponentAuthorityMap;
//
//	TMap<Worker_RequestId, USpatialActorChannel*> PendingActorRequests;
//
//	TFunction<AActor*()> OnSpawnRequest;
//
//	class USpatialPackageMapClient* PackageMap;
//
//	USpatialReceiver* EntityPipeline;
//};