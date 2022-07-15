#pragma once
#include "framework.h"
#include <future>
#include <locale>
#include <iostream>
#include <string>
#include <Windows.h>
#include <string>
#include <iomanip>
#include <fstream>
namespace Net
{
	static char (*IsNetRelevantFor)(AActor*, AActor*, AActor*, FVector&);
	bool(*ReplicateActor)(UActorChannel*);
	void(*CallPreReplication)(AActor*, UNetDriver*);
	static void (*CloseActorChannel)(UActorChannel*);
	UChannel* (*CreateChannel)(UNetConnection*, int, bool, int32_t);
	void(*SendClientAdjustment)(AActor*);
	__int64(*SetChannelActor)(UActorChannel*, AActor*);

	std::vector<AActor*> PrivateObjectList;

	struct ProcessConnectionParams
	{
		int* Connections;
		UNetConnection* Connection;
		std::vector<AActor*> ConsiderList;
	};

	static char (*InitHost)(AOnlineBeaconHost*);
	static void (*SetWorld)(UNetDriver*, UWorld*);
	static void (*ServerReplicateActors)(UReplicationDriver*);
	static void (*MarkArrayDirty)(FFastArraySerializer*);

	inline UActorChannel* FindChannel(AActor* Actor, UNetConnection* Connection)
	{
		static auto ActorChannelClass = UActorChannel::StaticClass();

		for (int i = 0; i < Connection->OpenChannels.Num(); i++)
		{
			auto Channel = Connection->OpenChannels[i];

			if (Channel && Channel->Class)
			{
				if (Channel->Class == ActorChannelClass)
				{
					if (((UActorChannel*)Channel)->Actor == Actor)
						return ((UActorChannel*)Channel);
				}
			}
		}

		return NULL;
	}

	static bool IsActorRelevant(AActor* Actor, AActor* Viewer)
	{
		auto Loc = Viewer->K2_GetActorLocation();

		if (IsNetRelevantFor(Actor, Viewer, Viewer, Loc))
		{
			return true;
		}

		return false;
	}

	inline UActorChannel* ReplicateToClient(AActor* InActor, UNetConnection* InConnection)
	{
		if (InActor->IsA(APlayerController::StaticClass()) && InActor != InConnection->PlayerController)
			return nullptr;

		auto Channel = (UActorChannel*)(CreateChannel(InConnection, 2, true, -1));

		if (Channel) {
			SetChannelActor(Channel, InActor);
			Channel->Connection = InConnection;
		}

		return Channel;
	}


	void ProcessConnection(ProcessConnectionParams* Params) {
		auto Connection = Params->Connection;
		auto ConsiderList = Params->ConsiderList;

		if (!Connection->ViewTarget)
		{
			*Params->Connections++;
			return;
		}

		if (Connection->PlayerController)
			SendClientAdjustment(Connection->PlayerController);

		for (auto Actor : ConsiderList)
		{
			auto Channel = FindChannel(Actor, Connection);

			if (!Actor->bAlwaysRelevant && !Actor->bNetUseOwnerRelevancy && !Actor->bOnlyRelevantToOwner)
			{
				if (!IsActorRelevant(Actor, Connection->ViewTarget))
				{
					if (Channel)
						CloseActorChannel(Channel);
					continue;
				}
			}

			if (!Channel)
				Channel = ReplicateToClient(Actor, Connection);

			if (Channel)
				ReplicateActor(Channel);
		}

		*Params->Connections++;
	}

	

	std::vector<AActor*>& GetNetworkObjectList()
	{
		return PrivateObjectList;
	}

	void BuildConsiderList(UNetDriver* NetDriver, std::vector<AActor*>& OutConsiderList) {
		std::vector<AActor*> ActorsToRemove = std::vector<AActor*>();

		for (auto Actor : GetNetworkObjectList())
		{
			if (!Actor)
				continue;

			if (Actor->bActorIsBeingDestroyed)
			{
				ActorsToRemove.push_back(Actor);
				continue;
			}

			if (Actor->RemoteRole == ENetRole::ROLE_None)
			{
				ActorsToRemove.push_back(Actor);
				continue;
			}

			if (Actor->NetDriverName.ComparisonIndex != NetDriver->NetDriverName.ComparisonIndex)
				continue;

			if (Actor->NetDormancy == ENetDormancy::DORM_Initial && Actor->bNetStartup)
			{
				ActorsToRemove.push_back(Actor);
				continue;
			}

			if (!Actor->bReplicates)
				continue;

			if (Actor->Name.ComparisonIndex != 0)
			{
				CallPreReplication(Actor, NetDriver);
				OutConsiderList.push_back(Actor);
			}
		}

		for (auto Actor : ActorsToRemove)
			GetNetworkObjectList().erase(std::find(GetNetworkObjectList().begin(), GetNetworkObjectList().end(), Actor));

		ActorsToRemove.clear();
		ActorsToRemove.empty();
	}

	inline int PrepConnections(UNetDriver* NetDriver) {
		int ReadyConnections = 0;

		for (int ConnIdx = 0; ConnIdx < NetDriver->ClientConnections.Num(); ConnIdx++)
		{
			UNetConnection* Connection = NetDriver->ClientConnections[ConnIdx];
			if (!Connection) continue;

			AActor* OwningActor = Connection->OwningActor;

			if (OwningActor)
			{
				ReadyConnections++;
				AActor* DesiredViewTarget = OwningActor;

				if (Connection->PlayerController)
				{
					if (AActor* ViewTarget = Connection->PlayerController->GetViewTarget())
					{
						DesiredViewTarget = ViewTarget;
					}
				}

				Connection->ViewTarget = DesiredViewTarget;

				for (int ChildIdx = 0; ChildIdx < Connection->Children.Num(); ++ChildIdx)
				{
					UNetConnection* ChildConnection = Connection->Children[ChildIdx];
					if (ChildConnection && ChildConnection->PlayerController && ChildConnection->ViewTarget)
					{
						ChildConnection->ViewTarget = DesiredViewTarget;
					}
				}
			}
			else
			{
				Connection->ViewTarget = nullptr;

				for (int ChildIdx = 0; ChildIdx < Connection->Children.Num(); ++ChildIdx)
				{
					UNetConnection* ChildConnection = Connection->Children[ChildIdx];
					if (ChildConnection && ChildConnection->PlayerController && ChildConnection->ViewTarget)
					{
						ChildConnection->ViewTarget = nullptr;
					}
				}
			}
		}

		return ReadyConnections;
	}

	void Tick(UNetDriver* NetDriver) {
		++* (DWORD*)(__int64(NetDriver) + 816);

		auto NumClientsToTick = PrepConnections(NetDriver);

		if (NumClientsToTick == 0)
			return;

		std::vector<AActor*> ConsiderList = std::vector<AActor*>();
		BuildConsiderList(NetDriver, ConsiderList);

		int ProcessedConnections = 0;
		int ConnectionsToProcess = NetDriver->ClientConnections.Num();

		for (int i = 0; i < NetDriver->ClientConnections.Num(); i++) {
			auto Connection = NetDriver->ClientConnections[i];

			if (!Connection->ViewTarget)
				continue;

			if ((*(__int64(__fastcall**)(__int64))(*(__int64*)Connection + 664))(*(__int64*)((__int64)Connection)))
			{
				ProcessedConnections++;
				continue;
			}
			auto fut = std::async(std::launch::async, ProcessConnection, new ProcessConnectionParams{ &ProcessedConnections, Connection, ConsiderList });
			fut.get();
		}

		while (ConnectionsToProcess != ProcessedConnections)
		{
			continue;
		}

		ConsiderList.empty();
		ConsiderList.clear();
	}
	
	static void Init()
	{
		/*uintptr_t IsNetRelevantForSig;
		uintptr_t ReplicateActorSig;
		uintptr_t CallPreRepSig;
		uintptr_t ActorChannelCloseSig;
		uintptr_t CreateChannelSig;
		uintptr_t SendClientAdjustmentSig;
		uintptr_t SetChannelActorSig;
		IsNetRelevantForSig = Memory::FindPattern("48 89 5C 24 ? 56 57 41 56 48 83 EC 70 48 8B FA 4D 8B F1 0F B6 91 ? ? ? ? 49 8B D8 48 8B F1 F6 C2 10 0F 85 ? ? ? ? 48 8B C1 0F 1F 40 00");
		ReplicateActorSig = Memory::FindPattern("48 8B C4 48 89 48 08 55 53 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 A8 0F 29 78 98 48 89 70 E8 4C 89 60 D8");
		CallPreRepSig = Memory::FindPattern("48 85 D2 0F 84 ? ? ? ? 56 41 56 48 83 EC 38 4C 8B F2 48 89 5C 24 ? 48 89 6C 24 ? 48 8D 54 24 ? 48 8B F1");
		ActorChannelCloseSig = Memory::FindPattern("48 89 5C 24 ? 55 57 41 57 48 83 EC 50 33 FF 48 8B D9 89 7C 24 70 80 3D ? ? ? ? ? 44 8D 7F 01 0F 82 ? ? ? ? 48 8B 49 68 48 85 C9 74 26 45 33 C0 48 8D 54 24 ?");
		CreateChannelSig = Memory::FindPattern("40 56 57 41 54 41 55 41 57 48 83 EC 60 48 8B 01 41 8B F9 45 0F B6 E0 4C 63 FA 48 8B F1");
		SendClientAdjustmentSig = Memory::FindPattern("40 53 48 83 EC 20 48 8B 99 ? ? ? ? 48 39 99 ? ? ? ? 74 0A 48 83 B9 ? ? ? ? ? 74 78 48 85 DB 75 0C 48 8B 99 ? ? ? ?");
		SetChannelActorSig = Memory::FindPattern("48 8B C4 55 53 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 48 89 70 10 48 8B D9 48 89 78 18");*/
		auto BaseAddr = (uintptr_t)GetModuleHandle(0);
		InitHost = decltype(InitHost)(BaseAddr + 0x39DAB0);
		SetWorld = decltype(SetWorld)(BaseAddr + 0x2298C60);
		ServerReplicateActors = decltype(ServerReplicateActors)(BaseAddr + 0x700820);
		MarkArrayDirty = decltype(MarkArrayDirty)(BaseAddr + 0x340210);
		/*IsNetRelevantFor = decltype(IsNetRelevantFor)(IsNetRelevantForSig);
		ReplicateActor = decltype(ReplicateActor)(ReplicateActorSig);
		CallPreReplication = decltype(CallPreReplication)(CallPreRepSig);
		CloseActorChannel = decltype(CloseActorChannel)(ActorChannelCloseSig);
		CreateChannel = decltype(CreateChannel)(CreateChannelSig);
		SetChannelActor = decltype(SetChannelActor)(SetChannelActorSig);*/


		auto Beacon = GetWorld()->SpawnActor<AFortOnlineBeaconHost>({}, {});
		Beacon->ListenPort = 7777;

		if (!InitHost(Beacon))
		{
			UE_LOG(LogNet, "AOnlineBeaconHost::InitHost failed");
			return;
		}

		GetWorld()->NetDriver = Beacon->NetDriver;
		GetWorld()->NetDriver->NetDriverName = FName(282);
		SetWorld(GetWorld()->NetDriver, GetWorld());
		GetWorld()->LevelCollections[0].NetDriver = GetWorld()->NetDriver;
		GetWorld()->LevelCollections[1].NetDriver = GetWorld()->NetDriver;

		GetWorld()->AuthorityGameMode->GameSession->MaxPlayers = 100;

		auto a1 = (__int64*)GetWorld()->NetDriver;
		auto v16 = (__int64)NewObject<UFortReplicationGraph>(GetWorld()->NetDriver);

		a1[163] = v16;
		if (v16)
		{
			(*(void(__fastcall**)(__int64, __int64*))(*(__int64*)v16 + 568))(v16, a1);
			(*(void(__fastcall**)(__int64, __int64))(*(__int64*)a1[163] + 576))(a1[163], a1[23]);
		}

		UE_LOG(LogNet, "Listening on port {}", Beacon->ListenPort);
	}
}