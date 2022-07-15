#pragma once
#include "framework.h"

namespace Inventory
{
	static void AddItem(AFortPlayerControllerAthena* PlayerController, UFortItemDefinition* ItemDef, EFortQuickBars QuickBar, int Slot, int Count, bool bAddToQuickbar = true)
	{
		if (!ItemDef || !PlayerController)
			return;

		auto ItemInstance = (UFortWorldItem*)ItemDef->CreateTemporaryItemInstanceBP(1, 0);
		if (ItemInstance)
		{
			ItemInstance->ItemEntry.Count = Count;
			ItemInstance->SetOwningControllerForTemporaryItem(PlayerController);

			PlayerController->WorldInventory->Inventory.ItemInstances.Add(ItemInstance);
			PlayerController->WorldInventory->Inventory.ReplicatedEntries.Add(ItemInstance->ItemEntry);

			if (bAddToQuickbar)
				PlayerController->QuickBars->ServerAddItemInternal(ItemInstance->GetItemGuid(), QuickBar, Slot);
		}
	}

	static void AddItemToInventory(UFortItemDefinition* ItemDefinition, EFortQuickBars Quickbar, AFortPlayerController* TargetController, int count, int Slot)
	{
		if (!ItemDefinition)
		{
			printf("Invalid Item Definition\n");
			return;
		}


		auto Inventory = TargetController->WorldInventory;

		auto QuickBars = TargetController->QuickBars;

		if (Quickbar == EFortQuickBars::Secondary)
		{
			UFortWorldItem* ItemInstance = nullptr;

			for (int i = 0; i < Inventory->Inventory.ItemInstances.Num(); i++)
			{
				if (Inventory->Inventory.ItemInstances[i]->GetItemDefinitionBP() == ItemDefinition)
					ItemInstance = Inventory->Inventory.ItemInstances[i];
			}

			if (ItemInstance)
			{
				auto NewCount = ItemInstance->ItemEntry.Count + count;
				for (int i = 0; i < Inventory->Inventory.ReplicatedEntries.Num(); i++)
				{
					if (Inventory->Inventory.ReplicatedEntries[i].ItemDefinition == ItemDefinition)
					{
						Inventory->Inventory.ReplicatedEntries[i].Count = NewCount;
						Inventory->Inventory.ReplicatedEntries[i].ReplicationKey++;
					}
				}
				ItemInstance->ItemEntry.Count = NewCount;
				ItemInstance->ItemEntry.ReplicationKey++;
				return;
			}
		}
	}

	static void UpdateInventory(AFortPlayerControllerAthena* PlayerController)
	{
		PlayerController->HandleWorldInventoryLocalUpdate();

		PlayerController->WorldInventory->HandleInventoryLocalUpdate();
		PlayerController->WorldInventory->bRequiresLocalUpdate = true;
		PlayerController->QuickBars->OnRep_PrimaryQuickBar();
		PlayerController->QuickBars->OnRep_SecondaryQuickBar();
		PlayerController->QuickBars->ForceNetUpdate();
		PlayerController->WorldInventory->ForceNetUpdate();

		Net::MarkArrayDirty(&PlayerController->WorldInventory->Inventory);
	}

	static void InitForPlayer(AFortPlayerControllerAthena* PlayerController) // no pull requests that modify the order of slots will be accepted
	{
		AddItem(PlayerController, Util::FindObjectFast<UFortItemDefinition>("/Game/Athena/Items/Weapons/WID_Harvest_Pickaxe_Athena_C_T01.WID_Harvest_Pickaxe_Athena_C_T01"), EFortQuickBars::Primary, 0, 1);
		AddItem(PlayerController, Util::FindObjectFast<UFortItemDefinition>("/Game/Items/Weapons/BuildingTools/BuildingItemData_Wall.BuildingItemData_Wall"), EFortQuickBars::Secondary, 0, 1);
		AddItem(PlayerController, Util::FindObjectFast<UFortItemDefinition>("/Game/Items/Weapons/BuildingTools/BuildingItemData_Floor.BuildingItemData_Floor"), EFortQuickBars::Secondary, 1, 1);
		AddItem(PlayerController, Util::FindObjectFast<UFortItemDefinition>("/Game/Items/Weapons/BuildingTools/BuildingItemData_Stair_W.BuildingItemData_Stair_W"), EFortQuickBars::Secondary, 2, 1);
		AddItem(PlayerController, Util::FindObjectFast<UFortItemDefinition>("/Game/Items/Weapons/BuildingTools/BuildingItemData_RoofS.BuildingItemData_RoofS"), EFortQuickBars::Secondary, 3, 1);
		AddItem(PlayerController, Util::FindObjectFast<UFortItemDefinition>("/Game/Items/ResourcePickups/WoodItemData.WoodItemData"), EFortQuickBars::Secondary, 0, 999);
		AddItem(PlayerController, Util::FindObjectFast<UFortItemDefinition>("/Game/Items/ResourcePickups/StoneItemData.StoneItemData"), EFortQuickBars::Secondary, 0, 999);
		AddItem(PlayerController, Util::FindObjectFast<UFortItemDefinition>("/Game/Items/ResourcePickups/MetalItemData.MetalItemData"), EFortQuickBars::Secondary, 0, 999);
		AddItem(PlayerController, Util::FindObjectFast<UFortItemDefinition>("/Game/Athena/Items/Weapons/WID_Shotgun_Standard_Athena_UC_Ore_T03.WID_Shotgun_Standard_Athena_UC_Ore_T03"), EFortQuickBars::Primary, 1, 1);
		AddItem(PlayerController, Util::FindObjectFast<UFortItemDefinition>("/Game/Athena/Items/Weapons/WID_Assault_Auto_Athena_R_Ore_T03.WID_Assault_Auto_Athena_R_Ore_T03"), EFortQuickBars::Primary, 2, 1);

		UpdateInventory(PlayerController);
	}
}