#pragma once
#include "framework.h"

namespace Abilities
{
	static bool (*InternalTryActivateAbility)(UAbilitySystemComponent*, FGameplayAbilitySpecHandle Handle, FPredictionKey InPredictionKey, UGameplayAbility** OutInstancedAbility, void* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData);

	static void Init()
	{
		auto BaseAddr = (uintptr_t)GetModuleHandle(0);
		auto InternalTryActivateAbilityAddr = BaseAddr + 0x581590;

		InternalTryActivateAbility = decltype(InternalTryActivateAbility)(InternalTryActivateAbilityAddr);
	}
}