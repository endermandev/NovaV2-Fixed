#pragma once
#include "framework.h"
#include <random>
#include <map>
#include "Gamemodes.hpp"

namespace Hooks
{
	static void* (*ProcessEvent)(void*, void*, void*);
	static void* (*SetClientLoginState)(UNetConnection*, int);
	static void* (*TickFlush)(UNetDriver* NetDriver);

	UKismetMathLibrary* KSM;

	UGameplayStatics* UGS;

	static std::vector<ABuildingSMActor*> ExistingBuildings;

	std::vector<std::string> AthenaConsumables = {
		"/Game/Athena/Items/Consumables/Shields/Athena_Shields.Athena_Shields",
		"/Game/Athena/Items/Consumables/ShieldSmall/Athena_ShieldSmall.Athena_ShieldSmall",
		"/Game/Athena/Items/Consumables/PurpleStuff/Athena_PurpleStuff.Athena_PurpleStuff",
		"/Game/Athena/Items/Consumables/SuperMedkit/Athena_SuperMedkit.Athena_SuperMedkit",
		"/Game/Athena/Items/Consumables/Medkit/Athena_Medkit.Athena_Medkit"
	};

	std::vector<std::string> AthenaLootPool = {
		"/Game/Athena/Items/Weapons/WID_Assault_AutoHigh_Athena_SR_Ore_T03.WID_Assault_AutoHigh_Athena_SR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Assault_AutoHigh_Athena_VR_Ore_T03.WID_Assault_AutoHigh_Athena_VR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Assault_Auto_Athena_R_Ore_T03.WID_Assault_Auto_Athena_R_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Assault_Auto_Athena_UC_Ore_T03.WID_Assault_Auto_Athena_UC_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Assault_Auto_Athena_C_Ore_T02.WID_Assault_Auto_Athena_C_Ore_T02",
		"/Game/Athena/Items/Weapons/WID_Shotgun_Standard_Athena_C_Ore_T03.WID_Shotgun_Standard_Athena_C_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Shotgun_Standard_Athena_C_Ore_T03.WID_Shotgun_Standard_Athena_C_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Shotgun_Standard_Athena_UC_Ore_T03.WID_Shotgun_Standard_Athena_UC_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Shotgun_SemiAuto_Athena_UC_Ore_T03.WID_Shotgun_SemiAuto_Athena_UC_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Shotgun_SemiAuto_Athena_R_Ore_T03.WID_Shotgun_SemiAuto_Athena_R_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Shotgun_SemiAuto_Athena_VR_Ore_T03.WID_Shotgun_SemiAuto_Athena_VR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Shotgun_SlugFire_Athena_VR.WID_Shotgun_SlugFire_Athena_VR",
		"/Game/Athena/Items/Weapons/WID_Shotgun_SlugFire_Athena_SR.WID_Shotgun_SlugFire_Athena_SR",
		"/Game/Athena/Items/Weapons/WID_Sniper_BoltAction_Scope_Athena_R_Ore_T03.WID_Sniper_BoltAction_Scope_Athena_R_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Sniper_BoltAction_Scope_Athena_VR_Ore_T03.WID_Sniper_BoltAction_Scope_Athena_VR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Sniper_BoltAction_Scope_Athena_SR_Ore_T03.WID_Sniper_BoltAction_Scope_Athena_SR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Sniper_Standard_Scope_Athena_VR_Ore_T03.WID_Sniper_Standard_Scope_Athena_VR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Sniper_Standard_Scope_Athena_SR_Ore_T03.WID_Sniper_Standard_Scope_Athena_SR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Pistol_AutoHeavyPDW_Athena_C_Ore_T03.WID_Pistol_AutoHeavyPDW_Athena_C_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Pistol_AutoHeavyPDW_Athena_UC_Ore_T03.WID_Pistol_AutoHeavyPDW_Athena_UC_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Pistol_AutoHeavyPDW_Athena_R_Ore_T03.WID_Pistol_AutoHeavyPDW_Athena_R_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Pistol_Scavenger_Athena_UC_Ore_T03.WID_Pistol_Scavenger_Athena_UC_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Pistol_Scavenger_Athena_R_Ore_T03.WID_Pistol_Scavenger_Athena_R_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Pistol_Scavenger_Athena_VR_Ore_T03.WID_Pistol_Scavenger_Athena_VR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Assault_LMG_Athena_VR_Ore_T03.WID_Assault_LMG_Athena_VR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Assault_LMG_Athena_SR_Ore_T03.WID_Assault_LMG_Athena_SR_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Pistol_SemiAuto_Athena_C_Ore_T02.WID_Pistol_SemiAuto_Athena_C_Ore_T02",
		"/Game/Athena/Items/Weapons/WID_Pistol_SemiAuto_Athena_UC_Ore_T03.WID_Pistol_SemiAuto_Athena_UC_Ore_T03",
		"/Game/Athena/Items/Weapons/WID_Pistol_SemiAuto_Athena_R_Ore_T03.WID_Pistol_SemiAuto_Athena_R_Ore_T03",
	};

	std::vector<std::string> TrapsPool = {
		"/Game/Athena/Items/Traps/TID_Floor_Player_Launch_Pad_Athena.TID_Floor_Player_Launch_Pad_Athena",
		"/Game/Athena/Items/Traps/TID_Floor_Spikes_Athena_R_T03.TID_Floor_Spikes_Athena_R_T03"
	};

	std::vector<std::string> ResourcePool = {
		"/Game/Items/ResourcePickups/WoodItemData.WoodItemData",
		"/Game/Items/ResourcePickups/StoneItemData.StoneItemData",
		"/Game/Items/ResourcePickups/MetalItemData.MetalItemData",
		"/Game/Athena/Items/Consumables/TowerGrenade/Athena_TowerGrenade.Athena_TowerGrenade"
	};

	std::vector<std::string> AmmoPool = {
		"/Game/Athena/Items/Ammo/AmmoDataRockets.AmmoDataRockets",
		"/Game/Athena/Items/Ammo/AthenaAmmoDataShells.AthenaAmmoDataShells",
		"/Game/Athena/Items/Ammo/AthenaAmmoDataBulletsMedium.AthenaAmmoDataBulletsMedium",
		"/Game/Athena/Items/Ammo/AthenaAmmoDataBulletsLight.AthenaAmmoDataBulletsLight",
		"/Game/Athena/Items/Ammo/AthenaAmmoDataBulletsHeavy.AthenaAmmoDataBulletsHeavy"
	};

	static UFortItemDefinition* GetRandomItemDefinition()
	{
		while (true)
		{
			auto Idx = KSM->STATIC_RandomInteger(AthenaLootPool.size());
			auto Item = AthenaLootPool[Idx];
			auto Def = Util::FindObjectFast<UFortItemDefinition>(Item);
			if (!Def)
				continue;

			auto rng = std::default_random_engine{};
			std::shuffle(AthenaLootPool.begin(), AthenaLootPool.end(), rng);
			return Def;
		}
	}

	static UFortItemDefinition* GetRandomConsumableItemDefinition()
	{
		while (true)
		{
			auto Idx = KSM->STATIC_RandomInteger(AthenaConsumables.size());
			auto Item = AthenaConsumables[Idx];
			auto Def = Util::FindObjectFast<UFortItemDefinition>(Item);
			if (!Def)
				continue;

			auto rng = std::default_random_engine{};
			std::shuffle(AthenaConsumables.begin(), AthenaConsumables.end(), rng);
			return Def;
		}
	}

	static UFortItemDefinition* GetRandomResourceItemDefinition()
	{
		while (true)
		{
			auto Idx = KSM->STATIC_RandomInteger(ResourcePool.size());
			auto Item = ResourcePool[Idx];
			auto Def = Util::FindObjectFast<UFortItemDefinition>(Item);
			if (!Def)
				continue;

			auto rng = std::default_random_engine{};
			std::shuffle(ResourcePool.begin(), ResourcePool.end(), rng);
			return Def;
		}
	}

	static UFortAmmoItemDefinition* GetRandomAmmoItemDefinition()
	{
		while (true)
		{
			auto Idx = KSM->STATIC_RandomInteger(AmmoPool.size());
			auto Item = AmmoPool[Idx];
			auto Def = Util::FindObjectFast<UFortAmmoItemDefinition>(Item);
			if (!Def)
				continue;

			auto rng = std::default_random_engine{};
			std::shuffle(AmmoPool.begin(), AmmoPool.end(), rng);
			return Def;
		}
	}

	static AFortPickupAthena* SpawnPickup(FVector Location, UFortItemDefinition* ItemDef = GetRandomItemDefinition(), int Count = 1)
	{
		if (Count == 1 && ItemDef->IsA(UFortAmmoItemDefinition::StaticClass()))
			Count = ((UFortAmmoItemDefinition*)(ItemDef))->DropCount;

		auto Pickup = GetWorld()->SpawnActor<AFortPickupAthena>(Location, {});

		Pickup->PrimaryPickupItemEntry.ItemDefinition = ItemDef;
		Pickup->PrimaryPickupItemEntry.Count = Count;

		Pickup->TossPickup(Location, nullptr, 6, true);

		return Pickup;
	}

	static AFortPickupAthena* SpawnPickupOther(FVector Location, UFortItemDefinition* ItemDef, int Count = 1)
	{
		if (Count == 1 && ItemDef->IsA(UFortAmmoItemDefinition::StaticClass()))
			Count = ((UFortAmmoItemDefinition*)(ItemDef))->DropCount;

		auto Pickup = GetWorld()->SpawnActor<AFortPickupAthena>(Location, {});

		Pickup->PrimaryPickupItemEntry.ItemDefinition = ItemDef;
		Pickup->PrimaryPickupItemEntry.Count = Count;

		Pickup->TossPickup(Location, nullptr, 6, true);

		return Pickup;
	}

	bool GuidComp(FGuid guidA, FGuid guidB)
	{
		if (guidA.A == guidB.A && guidA.B == guidB.B && guidA.C == guidB.C && guidA.D == guidB.D)
			return true;
		else
			return false;
	}

	static FVector CalculateSpectatorPawnLocation(AActor* TargetPawn)
	{
		auto FirstVect = TargetPawn->K2_GetActorLocation();
		auto SecondVect = FVector{ FirstVect.X, FirstVect.Y, FirstVect.Z + 150 };
		auto ThirdVect = FVector{ FirstVect.X - 500, FirstVect.Y, FirstVect.Z };

		return ThirdVect;
	}

	static AActor* GetRandomPlayerToSpectate(AFortPlayerController* SpectatorPC)
	{
		for (int i = 0; i < GetWorld()->NetDriver->ClientConnections.Num(); i++)
		{
			auto Connection = GetWorld()->NetDriver->ClientConnections[i];
			auto PlayerController = (AFortPlayerController*)Connection->PlayerController;
			auto Pawn = (AFortPlayerPawn*)PlayerController->Pawn;

			if (!PlayerController)
				continue;

			if (!Pawn)
				continue;

			if (Pawn->IsDead())
				continue;

			if (SpectatorPC == PlayerController)
				continue;

			return Pawn;

		}

		return nullptr;
	}

	/*bool CanBuild(ABuildingSMActor* BuildingActor)
	{
		bool bCanBuild = true;

		for (auto Building : ExistingBuildings)
		{
			if (!Building)
				continue;

			auto BuildX = Building->K2_GetActorLocation().X;
			auto BuildActorX = BuildingActor->K2_GetActorLocation().X;

			auto BuildY = Building->K2_GetActorLocation().Y;
			auto BuildActorY = BuildingActor->K2_GetActorLocation().Y;

			auto BuildZ = Building->K2_GetActorLocation().Z;
			auto BuildActorZ = BuildingActor->K2_GetActorLocation().Z;
			if (BuildX == BuildActorX && BuildY == BuildActorY && BuildZ == BuildActorZ && Building->BuildingType == BuildingActor->BuildingType)
			{
				bCanBuild = false;
			}
		}

		if (bCanBuild || ExistingBuildings.size() == 0)
		{
			ExistingBuildings.push_back(BuildingActor);
			return true;
		}

		return false;
	}*/

	static UFortWorldItem* GetInstanceFromGuid(AController* PC, const FGuid& ToFindGuid)
	{
		auto& ItemInstances = static_cast<AFortPlayerController*>(PC)->WorldInventory->Inventory.ItemInstances;

		for (int j = 0; j < ItemInstances.Num(); j++)
		{
			auto ItemInstance = ItemInstances[j];

			if (!ItemInstance)
				continue;

			auto Guid = ItemInstance->ItemEntry.ItemGuid;

			if (ToFindGuid.A == Guid.A && ToFindGuid.B == Guid.B && ToFindGuid.C == Guid.C && ToFindGuid.D == Guid.D)
			{
				return ItemInstance;
			}
		}

		return nullptr;
	}

	//static bool RemoveItemFromSlot(AFortPlayerControllerAthena* Controller, int Slot, EFortQuickBars Quickbars = EFortQuickBars::Primary, int Amount = -1) // -1 for all items in the slot
	//{
	//	auto& PrimarySlots = Controller->QuickBars->PrimaryQuickBar.Slots;
	//	auto& SecondarySlots = Controller->QuickBars->SecondaryQuickBar.Slots;

	//	bool bPrimaryQuickBar = (Quickbars == EFortQuickBars::Primary);

	//	if (Amount == -1)
	//	{
	//		if (bPrimaryQuickBar)
	//			Amount = PrimarySlots[Slot].Items.Num();
	//		else
	//			Amount = SecondarySlots[Slot].Items.Num();
	//	}

	//	bool bWasSuccessful = false;

	//	for (int i = 0; i < Amount; i++)
	//	{
	//		// todo add a check to make sure the slot has that amount of items
	//		auto& ToRemoveGuid = bPrimaryQuickBar ? PrimarySlots[Slot].Items[i] : SecondarySlots[Slot].Items[i];

	//		for (int j = 0; j < Controller->WorldInventory->Inventory.ItemInstances.Num(); j++)
	//		{
	//			auto ItemInstance = Controller->WorldInventory->Inventory.ItemInstances[j];

	//			if (!ItemInstance)
	//				continue;

	//			auto Guid = ItemInstance->ItemEntry.ItemGuid;

	//			if (ToRemoveGuid.A == Guid.A && ToRemoveGuid.B == Guid.B && ToRemoveGuid.C == Guid.C && ToRemoveGuid.D == Guid.D)
	//			{
	//				Controller->WorldInventory->Inventory.ItemInstances.RemoveAt(j);
	//				bWasSuccessful = true;
	//				// break;
	//			}
	//		}

	//		for (int x = 0; x < Controller->WorldInventory->Inventory.ReplicatedEntries.Num(); x++)
	//		{
	//			auto& ItemEntry = Controller->WorldInventory->Inventory.ReplicatedEntries[x];

	//			if (ItemEntry.ItemGuid.A == ToRemoveGuid.A && ItemEntry.ItemGuid.B == ToRemoveGuid.B && ItemEntry.ItemGuid.C == ToRemoveGuid.C && ItemEntry.ItemGuid.D == ToRemoveGuid.D)
	//			{
	//				Controller->WorldInventory->Inventory.ReplicatedEntries.RemoveAt(x);
	//				bWasSuccessful = true;

	//				// break;
	//			}
	//		}

	//		Controller->QuickBars->ServerRemoveItemInternal(ToRemoveGuid, false, true);
	//		ToRemoveGuid.Reset();
	//	}

	//	if (bWasSuccessful) // Make sure it acutally removed from the ItemInstances and ReplicatedEntries
	//	{
	//		Controller->QuickBars->EmptySlot(Quickbars, Slot);

	//		if (bPrimaryQuickBar)
	//			PrimarySlots[Slot].Items.FreeArray();
	//		else
	//			SecondarySlots[Slot].Items.FreeArray();

	//		// bPrimaryQuickBar ? PrimarySlots[Slot].Items.FreeArray() : SecondarySlots[Slot].Items.FreeArray();
	//	}

	//	Update(Controller, 0, true);

	//	return bWasSuccessful;
	//}
	


	static void* ProcessEventHook(UObject* Object, UFunction* Function, void* Params)
	{
		if (!Object || !Function)
			return ProcessEvent(Object, Function, Params);
		
		auto FuncName = Function->GetName();

		if (GetKeyState(VK_F7) & 1)
		{
			bool bStarted = false;
			if (!bStarted)
			{
				bStarted = true;

				auto EventPlayer = UObject::FindObject<ULevelSequencePlayer>("LevelSequencePlayer Athena_Gameplay_Geode.Athena_Gameplay_Geode.PersistentLevel.LevelSequence_LaunchRocket.AnimationPlayer");
				//auto EventPlayer = Util::FindObjectFast<ULevelSequencePlayer>("LevelSequencePlayer /Game/Athena/Maps/Test/Events/Athena_Gameplay_Geode.Athena_Gameplay_Geode.Athena_Gameplay_Geode.PersistentLevel.LevelSequence_LaunchRocket.AnimationPlayer");
				EventPlayer->Play();
			}
		}

		if (FuncName == "ServerExecuteInventoryItem")
		{
			auto ItemGuid = ((AFortPlayerController_ServerExecuteInventoryItem_Params*)Params)->ItemGuid;
			auto PlayerController = (AFortPlayerController*)Object;
			
			for (int i = 0; i < PlayerController->WorldInventory->Inventory.ItemInstances.Num(); i++)
			{
				auto ItemInstance = PlayerController->WorldInventory->Inventory.ItemInstances[i];

				if (Util::CompareGuid(ItemGuid, ItemInstance->GetItemGuid()))
				{
					if (auto Pawn = (AFortPlayerPawn*)PlayerController->Pawn)
					{
						auto Weap = Pawn->EquipWeaponDefinition((UFortWeaponItemDefinition*)ItemInstance->GetItemDefinitionBP(), ItemGuid);
						Weap->AmmoCount = 999;
						Weap->ClientGivenTo(Pawn);
						Pawn->ClientInternalEquipWeapon(Weap);
					}
				}
			}
		}

		if (FuncName.contains("ServerDBNOReviveStarted"))
		{
			auto CurrentParams = (AFortPlayerControllerAthena_ServerDBNOReviveStarted_Params*)Params;
			if (CurrentParams->DBNOPawn)
			{
				CurrentParams->DBNOPawn->bIsDBNO = false;
				CurrentParams->DBNOPawn->OnRep_IsDBNO();

				CurrentParams->DBNOPawn->SetHealth(30.0f);
			}
		}

		if (FuncName == "ServerAttemptInventoryDrop") {
			auto PlayerController = (AFortPlayerControllerAthena*)Object;
			auto CurrentParams = ((AFortPlayerController_ServerAttemptInventoryDrop_Params*)Params);
			auto ITEMGUID = CurrentParams->ItemGuid;
			auto Pawn = (AFortPlayerPawn*)PlayerController->Pawn;

			auto PawnLocation = Pawn->K2_GetActorLocation();

			if (!Params || !PlayerController) {
				return NULL;
			}

			auto& ItemInstances = PlayerController->WorldInventory->Inventory.ItemInstances;
			auto QuickBars = PlayerController->QuickBars;

			auto& PrimaryQuickBarSlots = QuickBars->PrimaryQuickBar.Slots;
			auto& SecondaryQuickBarSlots = QuickBars->SecondaryQuickBar.Slots;

			bool bWasSuccessful = false;

			for (int i = 1; i < PrimaryQuickBarSlots.Num(); i++)
			{
				if (PrimaryQuickBarSlots[i].Items.Data)
				{
					for (int j = 0; j < PrimaryQuickBarSlots[i].Items.Num(); j++)
					{
						if (PrimaryQuickBarSlots[i].Items[j].A == ITEMGUID.A && PrimaryQuickBarSlots[i].Items[j].B == ITEMGUID.B && PrimaryQuickBarSlots[i].Items[j].A == ITEMGUID.C && PrimaryQuickBarSlots[i].Items[j].D == ITEMGUID.D)
						{
							auto Instance = GetInstanceFromGuid(PlayerController, ITEMGUID);

							if (Instance)
							{
								auto Definition = Instance->ItemEntry.ItemDefinition;
								//auto SuccessfullyRemoved = RemoveItemFromSlot(PlayerController, i, EFortQuickBars::Primary, j + 1);

								if (Definition)
								{
									auto Pickup = SpawnPickup(PlayerController->Pawn->K2_GetActorLocation(), Definition, 1);
									Pickup->PrimaryPickupItemEntry.LoadedAmmo = Instance->GetLoadedAmmo();
									bWasSuccessful = true;
									break;
								}

								printf("Couldn't find a definition for the dropped item!");
							}
						}
					}
				}
			}

		}

		if (FuncName == "ServerTryActivateAbility")
		{
			auto AbilitySystemComponent = (UAbilitySystemComponent*)Object;
			auto CurrentParams = (UAbilitySystemComponent_ServerTryActivateAbility_Params*)Params;

			UGameplayAbility* InstancedAbility;
			Abilities::InternalTryActivateAbility(AbilitySystemComponent, CurrentParams->AbilityToActivate, CurrentParams->PredictionKey, &InstancedAbility, nullptr, nullptr);
		}

		if (FuncName == "ServerCreateBuildingActor")
		{
			auto CurrentParams = (AFortPlayerController_ServerCreateBuildingActor_Params*)Params;
			auto PlayerController = (AFortPlayerController*)Object;

			if (CurrentParams->BuildingClassData.BuildingClass)
			{
				//auto BuildingActor = GetWorld()->SpawnActor<ABuildingSMActor>(CurrentParams->BuildLoc, CurrentParams->BuildRot, CurrentParams->BuildingClassData.BuildingClass);
				//if (BuildingActor && CanBuild(BuildingActor)) {
				//	BuildingActor->DynamicBuildingPlacementType = EDynamicBuildingPlacementType::DestroyAnythingThatCollides;
				//	// BuildingActor->PlacedByPlacementTool();
				//	BuildingActor->InitializeKismetSpawnedBuildingActor(BuildingActor, PlayerController);
				//	auto PlayerState = (AFortPlayerStateAthena*)PlayerController->PlayerState;
				//	BuildingActor->Team = PlayerState->TeamIndex;
				//}
				//else {
				//	BuildingActor->SetActorScale3D({});
				//	BuildingActor->SilentDie();
				//}
				auto BuildingActor = GetWorld()->SpawnActor<ABuildingActor>(CurrentParams->BuildLoc, CurrentParams->BuildRot, CurrentParams->BuildingClassData.BuildingClass);
				BuildingActor->InitializeKismetSpawnedBuildingActor(BuildingActor, PlayerController);
				BuildingActor->Team = ((AFortPlayerStateAthena*)PlayerController->PlayerState)->TeamIndex;
				BuildingActor->OnRep_Team();
			}
		}

		if (FuncName.contains("ServerPlayEmoteItem")) {
			auto PlayerController = (AFortPlayerControllerAthena*)Object;
			auto Pawn = (APlayerPawn_Athena_C*)PlayerController->Pawn;
			auto CurrentParams = (AFortPlayerController_ServerPlayEmoteItem_Params*)Params;

			if (Pawn)
			{
				auto EmoteItem = CurrentParams->EmoteAsset;
				auto Animation = EmoteItem->GetAnimationHardReference(EFortCustomBodyType::All, EFortCustomGender::Both);

				if (Pawn->RepAnimMontageInfo.AnimMontage != Animation)
				{
					Pawn->RepAnimMontageInfo.AnimMontage = Animation;
					Pawn->RepAnimMontageInfo.PlayRate = 1;
					Pawn->RepAnimMontageInfo.IsStopped = false;
					Pawn->RepAnimMontageInfo.SkipPositionCorrection = true;

					Pawn->PlayAnimMontage(Animation, 1, FName());
					Pawn->OnRep_AttachmentMesh();
					Pawn->OnRep_AttachmentReplication();
					Pawn->OnRep_ReplicatedAnimMontage();
				}
			}
		}

		if (FuncName == "ServerHandlePickup") {
			auto Pawn = (AFortPlayerPawnAthena*)Object;
			auto PlayerController = (AFortPlayerControllerAthena*)Pawn->Controller;
			auto ServerHandlePickupParams = (AFortPlayerPawn_ServerHandlePickup_Params*)Params;

			auto Pickup = ServerHandlePickupParams->Pickup;
			if (Pickup && !Pickup->bPickedUp) {
				Pickup->bPickedUp = true;
				auto ItemDef = Pickup->PrimaryPickupItemEntry.ItemDefinition;
				auto ItemInstances = PlayerController->WorldInventory->Inventory.ItemInstances;
				auto QuickbarSlots = PlayerController->QuickBars->PrimaryQuickBar.Slots;

				Pickup->K2_DestroyActor();

				if (!ItemDef->IsA(UFortWeaponItemDefinition::StaticClass()))
				{
					Inventory::AddItem(PlayerController, ItemDef, EFortQuickBars::Secondary, 0, Pickup->PrimaryPickupItemEntry.Count);
					Inventory::UpdateInventory(PlayerController);
					return ProcessEvent(Object, Function, Params);
				}

				for (int i = 0; i < QuickbarSlots.Num(); i++)
				{
					if (QuickbarSlots[i].Items.Data == 0)
					{
						if (i >= 6)
						{
							int CurrentFocusedSlot = PlayerController->QuickBars->PrimaryQuickBar.CurrentFocusedSlot;

							if (i == 0)
								continue;

							i = CurrentFocusedSlot;

							FGuid CurrentFocusedGUID = QuickbarSlots[CurrentFocusedSlot].Items[0];

							for (int j = 0; j < ItemInstances.Num(); j++)
							{
								auto ItemInstance = ItemInstances[j];

								auto CurrentItemDef = ItemInstance->GetItemDefinitionBP();
								auto CurrentItemGuid = ItemInstance->GetItemGuid();

								if (GuidComp(CurrentItemGuid, CurrentFocusedGUID))
								{
									SpawnPickup(Pawn->K2_GetActorLocation(), CurrentItemDef);
								}
							}

							PlayerController->QuickBars->EmptySlot(EFortQuickBars::Primary, CurrentFocusedSlot);
						}

						Inventory::AddItem(PlayerController, ItemDef, EFortQuickBars::Primary, 0, 1);
						Inventory::UpdateInventory(PlayerController);
						break;
					}
				}
			}
		}

		if (FuncName == "ServerAttemptInteract") {
			auto PlayerController = (AFortPlayerControllerAthena*)Object;
			auto ServerAttemptParams = (AFortPlayerController_ServerAttemptInteract_Params*)Params;
			auto RecievingActor = ServerAttemptParams->ReceivingActor;

			if (RecievingActor && RecievingActor->Class->GetName().contains("Tiered_Chest")) {
				auto Chest = (ABuildingContainer*)RecievingActor;
				Chest->bAlreadySearched = true;
				Chest->OnRep_bAlreadySearched();
				auto Location = RecievingActor->K2_GetActorLocation();
				auto Definition = GetRandomItemDefinition();
				auto Pickup = SpawnPickup(Location, Definition);
				SpawnPickup(Location, GetRandomConsumableItemDefinition());
				SpawnPickup(Location, ((UFortWeaponItemDefinition*)Definition)->GetAmmoWorldItemDefinition_BP());
				SpawnPickup(Location, GetRandomResourceItemDefinition(), 1);

				return NULL;
			}
			if (RecievingActor && RecievingActor->Class->GetName().contains("Tiered_Short_Ammo")) {
				auto Ammo = (ABuildingContainer*)RecievingActor;
				Ammo->bAlreadySearched = true;
				Ammo->OnRep_bAlreadySearched();
				auto Location = RecievingActor->K2_GetActorLocation();
				for (int i = 0; i < 2; i++) {
					SpawnPickup(Location, GetRandomAmmoItemDefinition());
				}
			}
		}

		if (FuncName.contains("ServerBeginEditingBuildingActor"))
		{
			auto PlayerController = (AFortPlayerControllerAthena*)Object;
			auto Pawn = (AFortPlayerPawn*)PlayerController->Pawn;

			if (!Pawn)
				return ProcessEvent(Object, Function, Params);

			auto CurrentParams = (AFortPlayerController_ServerBeginEditingBuildingActor_Params*)Params;
			auto EditActor = CurrentParams->BuildingActorToEdit;

			if (!EditActor)
				return ProcessEvent(Object, Function, Params);

			auto EditToolDef = Util::FindObjectFast<UFortWeaponItemDefinition>("/Game/Items/Weapons/BuildingTools/EditTool.EditTool");
			auto EditTool = (AFortWeap_EditingTool*)Pawn->EquipWeaponDefinition(EditToolDef, FGuid{ rand() % 1000, rand() % 1000, rand() % 1000, rand() % 1000 });
			EditTool->EditActor = EditActor;
			EditTool->OnRep_EditActor();
		}

		if (FuncName == "ClientOnPawnDied") {
			auto CurrentParams = (AFortPlayerControllerZone_ClientOnPawnDied_Params*)Params;
			auto PlayerController = (AFortPlayerControllerAthena*)Object;

			if (CurrentParams->DeathReport.KillerPlayerState)
			{
				((AFortPlayerStateAthena*)CurrentParams->DeathReport.KillerPlayerState)->ClientReportKill((AFortPlayerStateAthena*)PlayerController->PlayerState);
				((AFortPlayerStateAthena*)CurrentParams->DeathReport.KillerPlayerState)->KillScore++;
				((AFortPlayerStateAthena*)CurrentParams->DeathReport.KillerPlayerState)->OnRep_Kills();
				((AFortPlayerStateAthena*)CurrentParams->DeathReport.KillerPlayerState)->OnRep_Score();
			}

			TArray<AActor*> Actors;
			UGS->STATIC_GetAllActorsOfClass(GetWorld(), APlayerPawn_Athena_C::StaticClass(), &Actors);

			if (PlayerController->WorldInventory)
			{
				for (int i = 0; i < PlayerController->WorldInventory->Inventory.ItemInstances.Num(); i++)
				{
					auto ItemInstance = PlayerController->WorldInventory->Inventory.ItemInstances[i];
					auto ItemDef = ItemInstance->GetItemDefinitionBP();

					if (ItemDef->IsA(UFortBuildingItemDefinition::StaticClass()))
						continue;

					if (ItemDef->IsA(UFortWeaponMeleeItemDefinition::StaticClass()))
						continue;

					SpawnPickup(PlayerController->K2_GetActorLocation(), ItemDef, ItemInstance->ItemEntry.Count);
				}

				if (Actors.Num() == 1 || Actors.Num() == 2 && Actors.Contains(PlayerController->Pawn))
				{
					for (int ConnIdx = 0; ConnIdx < GetWorld()->NetDriver->ClientConnections.Num(); ConnIdx++)
					{
						auto PlayerController = (AFortPlayerControllerAthena*)GetWorld()->NetDriver->ClientConnections[ConnIdx]->PlayerController;
						if (PlayerController->Pawn)
							PlayerController->ClientNotifyWon(PlayerController->Pawn, Util::FindObjectFast<UFortWeaponItemDefinition>("/Game/Athena/Items/Weapons/WID_Assault_Auto_Athena_R_Ore_T03.WID_Assault_Auto_Athena_R_Ore_T03"), EDeathCause::Rifle);
					}
					// CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&ShutdownThread, 0, 0, 0);
				}

				//PlayerController->ClientReturnToMainMenu(L"take this L, you need it.");

				for (int i = 0; i < Actors.Num(); i++)
				{
					auto Pawn = (APlayerPawn_Athena_C*)Actors[i];

					if (Pawn && !Pawn->IsDead() && Pawn != PlayerController->Pawn)
					{
						if (!PlayerController->SpectatorPawn)
						{
							PlayerController->SpectatorPawn = GetWorld()->SpawnActor<ASpectatorPawn>(FVector{0,0, 10000}, FRotator{0,0,0});
						}

						if (PlayerController->SpectatorPawn && Pawn)
						{
							if (CurrentParams->DeathReport.KillerPawn) {
								PlayerController->SetViewTargetWithBlend(CurrentParams->DeathReport.KillerPawn, 1.0, EViewTargetBlendFunction::VTBlend_EaseInOut, 1, true);
								PlayerController->SpectatorPawn->K2_SetActorLocation(CalculateSpectatorPawnLocation(CurrentParams->DeathReport.KillerPawn), false, true, new FHitResult());
								PlayerController->SpectatorPawn->K2_SetActorRotation(KSM->STATIC_FindLookAtRotation(PlayerController->SpectatorPawn->K2_GetActorLocation(), CurrentParams->DeathReport.KillerPawn->K2_GetActorLocation()), false);
								PlayerController->SpectatorPawn->SetActorEnableCollision(false);
								PlayerController->SpectatorPawn->SetActorHiddenInGame(true);
								PlayerController->SpectatorPawn->DisableInput(PlayerController);
								PlayerController->Possess(PlayerController->SpectatorPawn);
								PlayerController->SpectatorPawn->K2_AttachToActor(CurrentParams->DeathReport.KillerPawn, FName(), EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);
							}
							else {
								PlayerController->SetViewTargetWithBlend(GetRandomPlayerToSpectate(PlayerController), 1.0, EViewTargetBlendFunction::VTBlend_EaseInOut, 1, true);
								PlayerController->SpectatorPawn->K2_SetActorLocation(CalculateSpectatorPawnLocation(Pawn), false, true, new FHitResult());
								PlayerController->SpectatorPawn->K2_SetActorRotation(KSM->STATIC_FindLookAtRotation(PlayerController->SpectatorPawn->K2_GetActorLocation(), Pawn->K2_GetActorLocation()), false);
								PlayerController->SpectatorPawn->SetActorEnableCollision(false);
								PlayerController->SpectatorPawn->SetActorHiddenInGame(true);
								PlayerController->Possess(PlayerController->SpectatorPawn);
								PlayerController->SpectatorPawn->K2_AttachToActor(Pawn, FName(), EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);
							}
						}
						break;
					}
				}
				((AFortGameStateAthena*)GetWorld()->GameState)->PlayersLeft--;
			}
		}

		if (FuncName.contains("ServerEditBuildingActor"))
		{
			auto PlayerController = (AFortPlayerControllerAthena*)Object;
			auto CurrentParams = (AFortPlayerController_ServerEditBuildingActor_Params*)Params;

			/*if (CurrentParams->BuildingActorToEdit.IsBe)*/
			if (CurrentParams->BuildingActorToEdit && CurrentParams->NewBuildingClass)
			{
				auto Location = CurrentParams->BuildingActorToEdit->K2_GetActorLocation();
				auto Rotation = CurrentParams->BuildingActorToEdit->K2_GetActorRotation();


				/* UKismetMathLibrary::GridSnap_Float()

				 auto ForwardVector = CurrentParams->BuildingActorToEdit->GetActorForwardVector();
				 */

				Rotation.Yaw = Rotation.Yaw + (CurrentParams->RotationIterations * 90);
				//printf("Yaw %f Loc X %f Loc Y %f RIterations %i", Rotation.Yaw, ForwardVector.X, ForwardVector.Y, CurrentParams->RotationIterations);


				CurrentParams->BuildingActorToEdit->SetActorHiddenInGame(true);

				CurrentParams->BuildingActorToEdit->K2_DestroyActor();
				auto Building = GetWorld()->SpawnActor<ABuildingSMActor>(Location, Rotation, CurrentParams->NewBuildingClass);
				Building->bMirrored = CurrentParams->bMirrored;
				Building->InitializeKismetSpawnedBuildingActor(Building, PlayerController);
				Building->bMirrored = CurrentParams->bMirrored;
				Building->OnRep_CustomState();
				Building->Team = ((AFortPlayerStateAthena*)PlayerController->PlayerState)->TeamIndex;
				Building->OnRep_Team();
			}
		}

		if (FuncName == "ServerTryActivateAbilityWithEventData")
		{
			auto AbilitySystemComponent = (UAbilitySystemComponent*)Object;
			auto CurrentParams = (UAbilitySystemComponent_ServerTryActivateAbilityWithEventData_Params*)Params;

			UGameplayAbility* InstancedAbility;
			Abilities::InternalTryActivateAbility(AbilitySystemComponent, CurrentParams->AbilityToActivate, CurrentParams->PredictionKey, &InstancedAbility, nullptr, &CurrentParams->TriggerEventData);
		}
		
		if (FuncName == "ServerAttemptAircraftJump")
		{
			auto CurrentParams = (AFortPlayerControllerAthena_ServerAttemptAircraftJump_Params*)Params;
			auto PlayerController = (AFortPlayerControllerAthena*)Object;
			
			if (PlayerController->Pawn)
				return ProcessEvent(Object, Function, Params);

			auto GameState = (AAthena_GameState_C*)GetWorld()->GameState;
			auto Aircraft = GameState->GetAircraft(0);

			if (!Aircraft)
				return ProcessEvent(Object, Function, Params);

			auto Pawn = GetWorld()->SpawnActor<APlayerPawn_Athena_C>(Aircraft->K2_GetActorLocation(), {});
			PlayerController->Possess(Pawn);

			Pawn->bCanBeDamaged = true;

			PlayerController->SetControlRotation(CurrentParams->ClientRotation);
		}

		if (FuncName == "ServerAbilityRPCBatch")
		{
			auto AbilitySystemComponent = (UAbilitySystemComponent*)Object;
			auto CurrentParams = (UAbilitySystemComponent_ServerAbilityRPCBatch_Params*)Params;

			UGameplayAbility* InstancedAbility;
			Abilities::InternalTryActivateAbility(AbilitySystemComponent, CurrentParams->BatchInfo.AbilitySpecHandle, CurrentParams->BatchInfo.PredictionKey, &InstancedAbility, nullptr, nullptr);
		}

		if (FuncName == "ReadyToStartMatch")
		{
			static bool bInit = false;

			if (!bInit)
			{
				bInit = true;

				Net::Init();

				NewObject<UCheatManager>(GEngine->GameInstance->LocalPlayers[0]->PlayerController)->DestroyAll(AAthena_PlayerController_C::StaticClass());

				//auto GameState = (AAthena_GameState_C*)GetWorld()->GameState;

				auto GameState = (AFortGameStateAthena*)GetWorld()->GameState;

				GameState->CurrentPlaylistData = Util::FindObjectFast<UFortPlaylistAthena>("/Game/Athena/Playlists/Playlist_DefaultSolo.Playlist_DefaultSolo");
				//GameState->CurrentPlaylistData = Util::FindObjectFast<UFortPlaylistAthena>("/Game/Athena/Playlists/Playground/Playlist_Playground.Playlist_Playground");
				if (GameState->CurrentPlaylistData)
				{
					GameState->CurrentPlaylistData->bNoDBNO = false;
					GameState->CurrentPlaylistData->bIsLargeTeamGame = false;
					GameState->CurrentPlaylistData->FriendlyFireType = EFriendlyFireType::On;
					GameState->CurrentPlaylistData->bRewardsAllowXPProgression = true;
					GameState->OnRep_CurrentPlaylistData();
				}
				GameState->bGameModeWillSkipAircraft = true;
				GameState->WarmupCountdownEndTime = 99999.9f;
				GameState->GamePhase = EAthenaGamePhase::Warmup;
				GameState->OnRep_GamePhase(EAthenaGamePhase::None);

				auto GameMode = (AAthena_GameMode_C*)GetWorld()->AuthorityGameMode;

				GameMode->StartMatch();
				GameMode->StartPlay();
			}
		}

	    return ProcessEvent(Object, Function, Params);
	}

	auto RandomIntInRange(int min, int max)
	{
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 gen(rd()); // seed the generator
		static std::uniform_int_distribution<> distr(min, max); // define the range

		return distr(gen);
	}

	auto GetAllActorsOfClass(UClass* Class)
	{
		// You have to free this!!!
		TArray<AActor*> OutActors;

		static auto GameplayStatics = static_cast<UGameplayStatics*>(UGameplayStatics::StaticClass()->CreateDefaultObject());
		GameplayStatics->STATIC_GetAllActorsOfClass(GetWorld(), Class, &OutActors);

		return OutActors;
	}

	auto SpawnObject(UClass* Class, AFortPlayerControllerAthena* PC)
	{
		static auto GameplayStatics = static_cast<UGameplayStatics*>(UGameplayStatics::StaticClass()->CreateDefaultObject());
		GameplayStatics->STATIC_SpawnObject(UFortCheatManager::StaticClass(), PC);
	}

	FTransform GetSpawnLocation(AFortPlayerControllerAthena* PC) {
		TArray<AActor*> OutActors = GetAllActorsOfClass(AFortPlayerStartWarmup::StaticClass());
		auto ActorsNum = OutActors.Num();

		auto SpawnTransform = FTransform();
		SpawnTransform.Scale3D = FVector(1, 1, 1);
		SpawnTransform.Rotation = FQuat();
		SpawnTransform.Translation = FVector{ 1250, 1818, 3284 };

		if (ActorsNum != 0) {
			auto ActorToUseNum = RandomIntInRange(0, ActorsNum);
			auto ActorToUse = (OutActors)[ActorToUseNum];

			while (!ActorToUse)
			{
				ActorToUseNum = RandomIntInRange(0, ActorsNum);
				ActorToUse = (OutActors)[ActorToUseNum];
			}

			SpawnTransform.Translation = ActorToUse->K2_GetActorLocation();

			PC->WarmupPlayerStart = static_cast<AFortPlayerStartWarmup*>(ActorToUse);

		}

		// may cause memory leak in the future!!

		return SpawnTransform;

	}

	static void* SetClientLoginStateHook(UNetConnection* Connection, int State) // gets called in NMT_Join
	{
		if (State == 3)
		{
			if (auto PlayerController = (AFortPlayerControllerAthena*)Connection->PlayerController)
			{
				Connection->CurrentNetSpeed = 30000;
				auto PlayerState = (AFortPlayerStateAthena*)PlayerController->PlayerState;
				auto Pawn = (APlayerPawn_Athena_C*)GetWorld()->SpawnActor<APlayerPawn_Athena_C>(GetSpawnLocation(PlayerController).Translation, {});

				Pawn->bAlwaysRelevant = true;

				PlayerState->SetOwner(PlayerController);
				Pawn->Owner = PlayerController;
				Pawn->OnRep_Owner();

				Pawn->NetCullDistanceSquared = 0.f;

				PlayerController->Pawn = Pawn;
				PlayerController->AcknowledgedPawn = Pawn;
				PlayerController->OnRep_Pawn();
				PlayerController->Possess(Pawn);

				Pawn->HealthSet->Health.Minimum = 0;
				Pawn->HealthSet->CurrentShield.Minimum = 0;
				Pawn->NetUpdateFrequency *= 2;

				Pawn->SetMaxHealth(100);
				Pawn->SetMaxShield(100);

				Pawn->bCanBeDamaged = false;

				Pawn->bReplicateMovement = true;
				Pawn->OnRep_ReplicateMovement();

				PlayerController->bIsDisconnecting = false;
				PlayerController->bHasClientFinishedLoading = true;
				PlayerController->bHasServerFinishedLoading = true;
				PlayerController->bHasInitiallySpawned = true;
				PlayerController->OnRep_bHasServerFinishedLoading();

				
				PlayerState->bHasFinishedLoading = true;
				PlayerState->bHasStartedPlaying = true;
				PlayerState->OnRep_bHasStartedPlaying();

				

				PlayerController->QuickBars = GetWorld()->SpawnActor<AFortQuickBars>({}, {});
				PlayerController->QuickBars->SetOwner(PlayerController);
				PlayerController->QuickBars->OnRep_Owner();

				PlayerController->CheatManager = (UCheatManager*)UGS->STATIC_SpawnObject(UFortCheatManager::StaticClass(), PlayerController);

				PlayerController->OverriddenBackpackSize = 5;

				static auto FortRegisteredPlayerInfo = ((UFortGameInstance*)GetWorld()->OwningGameInstance)->RegisteredPlayers[0]; // UObject::FindObject<UFortRegisteredPlayerInfo>("FortRegisteredPlayerInfo Transient.FortEngine_0_1.FortGameInstance_0_1.FortRegisteredPlayerInfo_0_1");

				if (FortRegisteredPlayerInfo)
				{
					auto Hero = FortRegisteredPlayerInfo->AthenaMenuHeroDef;

					if (Hero)
					{
						UFortHeroType* HeroType = Hero->GetHeroTypeBP(); // UObject::FindObject<UFortHeroType>("FortHeroType HID_Outlander_015_F_V1_SR_T04.HID_Outlander_015_F_V1_SR_T04");
						PlayerState->HeroType = HeroType;
						PlayerState->OnRep_HeroType();

						
					}
				}

				PlayerState->CharacterParts[0] = Util::FindObjectFast<UCustomCharacterPart>("/Game/Characters/CharacterParts/Female/Medium/Heads/F_Med_Head1.F_Med_Head1");
				PlayerState->CharacterParts[1] = Util::FindObjectFast<UCustomCharacterPart>("/Game/Characters/CharacterParts/Female/Medium/Bodies/F_Med_Soldier_01.F_Med_Soldier_01");
				PlayerState->OnRep_CharacterParts();

				Inventory::InitForPlayer(PlayerController);

				auto AbilitySet = Util::FindObjectFast<UFortAbilitySet>("/Game/Abilities/Player/Generic/Traits/DefaultPlayer/GAS_DefaultPlayer.GAS_DefaultPlayer");

				for (int i = 0; i < AbilitySet->GameplayAbilities.Num(); i++)
					Util::GrantAbility(Pawn, AbilitySet->GameplayAbilities[i]);

				Util::GrantAbility(Pawn, Util::FindObjectFast<UClass>("/Game/Abilities/Weapons/Ranged/GA_Ranged_GenericDamage.GA_Ranged_GenericDamage_C"));

				PlayerController->bInfiniteAmmo = true;
				PlayerController->bInfiniteDurability = true;
				PlayerController->OverriddenBackpackSize = 100;


				switch (Gamemode::CurrentGM) {
					case Gamemode::Gamemodes::DUOS:
						// TODO, Add Teams for every pair of 2
						PlayerState->TeamIndex = EFortTeam(2);
						PlayerState->OnRep_PlayerTeam();
						PlayerState->SquadId = PlayerState->PlayerTeam->TeamMembers.Num() + 1;
						PlayerState->OnRep_SquadId();
						break;
					case Gamemode::Gamemodes::HIDEANDSEEK:
						PlayerState->TeamIndex = EFortTeam(2);
						PlayerState->OnRep_PlayerTeam();
						PlayerState->SquadId = PlayerState->PlayerTeam->TeamMembers.Num() + 1;
						PlayerState->OnRep_SquadId();
						break;
					default:
						PlayerState->OnRep_PlayerTeam();
						PlayerState->OnRep_SquadId();
						break;
				}

				Pawn->ForceNetUpdate();
				PlayerController->ForceNetUpdate();

				
				//Pawn->bAlwaysRelevant = true;

				//if (!Pawn)
				//	return PlayerController;

				//+
				//PlayerController->Pawn = Pawn;
				//Pawn->Owner = PlayerController;
				//Pawn->OnRep_Owner();
				//PlayerController->OnRep_Pawn();
				//PlayerController->Possess(Pawn);

				//Pawn->bCanBeDamaged = false;

				//Pawn->bReplicateMovement = true;
				//Pawn->OnRep_ReplicateMovement();


				//PlayerController->bHasClientFinishedLoading = true;
				//PlayerController->bHasServerFinishedLoading = true;
				//PlayerController->OnRep_bHasServerFinishedLoading();

				//PlayerState->bHasFinishedLoading = true;
				//PlayerState->bHasStartedPlaying = true;
				//PlayerState->OnRep_bHasStartedPlaying();

				//static auto HeroType = Util::FindObjectFast<UFortHeroType>("/Game/Athena/Heroes/HID_042_Athena_Commando_M_Cyberpunk.HID_042_Athena_Commando_M_Cyberpunk");

				//if (HeroType)
				//	PlayerState->HeroType = HeroType;

				//PlayerState->OnRep_HeroType();

				//PlayerController->QuickBars = GetWorld()->SpawnActor<AFortQuickBars>({}, {});
				//PlayerController->QuickBars->SetOwner(PlayerController);
				//PlayerController->QuickBars->OnRep_Owner();

				//PlayerController->OverriddenBackpackSize = 5;

				//static auto HeadCharacterPart = Util::FindObjectFast<UCustomCharacterPart>("/Game/Characters/CharacterParts/Female/Medium/Heads/F_Med_Head1.F_Med_Head1");
				//static auto BodyCharacterPart = Util::FindObjectFast<UCustomCharacterPart>("/Game/Characters/CharacterParts/Female/Medium/Bodies/F_Med_Soldier_01.F_Med_Soldier_01");

				//if (HeadCharacterPart)
				//	PlayerState->CharacterParts[0] = HeadCharacterPart;
				//if (BodyCharacterPart)
				//	PlayerState->CharacterParts[1] = BodyCharacterPart;

				//if (HeadCharacterPart || BodyCharacterPart)
				//	PlayerState->OnRep_CharacterParts();

				//Inventory::InitForPlayer(PlayerController);

				//Pawn->NetUpdateFrequency *= 2; // 100.0f is the Original
				//Pawn->SetMaxHealth(100);
				//Pawn->SetHealth(100);
				//Pawn->SetMaxShield(100);

				//auto AbilitySet = Util::FindObjectFast<UFortAbilitySet>("/Game/Abilities/Player/Generic/Traits/DefaultPlayer/GAS_DefaultPlayer.GAS_DefaultPlayer");

				//for (int i = 0; i < AbilitySet->GameplayAbilities.Num(); i++)
				//	Util::GrantAbility(Pawn, AbilitySet->GameplayAbilities[i]);

				//Util::GrantAbility(Pawn, Util::FindObjectFast<UClass>("/Game/Abilities/Weapons/Ranged/GA_Ranged_GenericDamage.GA_Ranged_GenericDamage_C"));

				////Pawn->ForceNetUpdate();
				////PlayerController->ForceNetUpdate();
			}
		}

		return SetClientLoginState(Connection, State);
	}

	static char KickPlayerHook(__int64, __int64)
	{
		return 0;
	}

	static void* TickFlushHook(UNetDriver* NetDriver)
	{
		if (NetDriver->IsA(UIpNetDriver::StaticClass()) && NetDriver->ClientConnections.Num() > 0 && NetDriver->ClientConnections[0]->InternalAck == false) {
			if (NetDriver->ReplicationDriver) {
				Net::ServerReplicateActors(NetDriver->ReplicationDriver);
			}
		}

		return TickFlush(NetDriver);
	}

	static void Init()
	{
		
		auto BaseAddr = (uintptr_t)GetModuleHandle(0);
		auto SetClientLoginStateAddr = BaseAddr + 0x2297FA0;
		auto KickPlayerAddr = BaseAddr + 0x216DEA0;
		auto ProcessEventAddr = BaseAddr + 0x158FB20;
		auto TickFlushAddr = BaseAddr + 0x2299FF0;
		auto CreateReplicationDriverAddr = BaseAddr + 0x2284200;

		CREATE_HOOK(ProcessEventAddr, ProcessEventHook, &ProcessEvent);
		CREATE_HOOK(SetClientLoginStateAddr, SetClientLoginStateHook, &SetClientLoginState);
		CREATE_HOOK(KickPlayerAddr, KickPlayerHook, nullptr);
		CREATE_HOOK(TickFlushAddr, TickFlushHook, &TickFlush);
	}
}