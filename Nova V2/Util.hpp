#pragma once
#include "framework.h"

namespace Util
{
	inline FGameplayAbilitySpecHandle* (*GiveAbility)(UAbilitySystemComponent* _this, FGameplayAbilitySpecHandle* outHandle, FGameplayAbilitySpec inSpec);
    inline UObject* (*StaticFindObject)(UClass*, UObject* Package, const wchar_t* OrigInName, bool ExactClass);

	static void GrantAbility(APlayerPawn_Athena_C* Pawn, UClass* Ability) // from raider
	{
        auto AbilitySystemComponent = Pawn->AbilitySystemComponent;

        if (!AbilitySystemComponent)
            return;

        auto GenerateNewSpec = [&]() -> FGameplayAbilitySpec
        {
            FGameplayAbilitySpecHandle Handle{ rand() };

            FGameplayAbilitySpec Spec{ -1, -1, -1, Handle, (UGameplayAbility*)Ability->CreateDefaultObject(), 1, -1, nullptr, 0, false, false, false };

            return Spec;
        };

        auto Spec = GenerateNewSpec();

        for (int i = 0; i < AbilitySystemComponent->ActivatableAbilities.Items.Num(); i++)
        {
            auto& CurrentSpec = AbilitySystemComponent->ActivatableAbilities.Items[i];

            if (CurrentSpec.Ability == Spec.Ability)
                return;
        }

        GiveAbility(AbilitySystemComponent, &Spec.Handle, Spec);
	}

    template <typename T>
    static T* FindObjectFast(std::string ObjectName, UClass* ObjectClass = nullptr)
    {
        auto OrigInName = std::wstring(ObjectName.begin(), ObjectName.end()).c_str();
        return (T*)StaticFindObject(ObjectClass, nullptr, OrigInName, false);
    }

    static bool CompareGuid(FGuid a, FGuid b)
    {
        return a.A == b.A && a.B == b.B && a.C == b.C && a.D == b.D;
    }

	static void Init()
	{
		auto BaseAddr = (uintptr_t)GetModuleHandle(0);
		GiveAbility = decltype(GiveAbility)(BaseAddr + 0x57FE50);
        StaticFindObject = decltype(StaticFindObject)(BaseAddr + 0x15B6350);
	}
}