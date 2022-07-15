// Fortnite (4.5-CL-4159770) SDK

#ifdef _MSC_VER
#pragma pack(push, 0x8)
#endif

#include "../SDK.hpp"
#include <Windows.h>

namespace SDK
{
	uintptr_t base_address = (uintptr_t)GetModuleHandle(NULL);
	TNameEntryArray* FName::GNames = *reinterpret_cast<SDK::TNameEntryArray**>((PBYTE)base_address + 0x21FD2C0);
	FUObjectArray* UObject::GObjects = reinterpret_cast<SDK::FUObjectArray*>((PBYTE)base_address + 0x4EB7DF8);

	//---------------------------------------------------------------------------
	bool FWeakObjectPtr::IsValid() const
	{
		if (ObjectSerialNumber == 0)
		{
			return false;
		}
		if (ObjectIndex < 0)
		{
			return false;
		}
		auto ObjectItem = UObject::GetGlobalObjects().GetItemByIndex(ObjectIndex);
		if (!ObjectItem)
		{
			return false;
		}
		if (!SerialNumbersMatch(ObjectItem))
		{
			return false;
		}
		return !(ObjectItem->IsUnreachable() || ObjectItem->IsPendingKill());
	}

	//---------------------------------------------------------------------------
	UObject* FWeakObjectPtr::Get() const
	{
		if (IsValid())
		{
			auto ObjectItem = UObject::GetGlobalObjects().GetItemByIndex(ObjectIndex);
			if (ObjectItem)
			{
				return ObjectItem->Object;
			}
		}
		return nullptr;
	}

	//---------------------------------------------------------------------------
}

#ifdef _MSC_VER
#pragma pack(pop)
#endif
