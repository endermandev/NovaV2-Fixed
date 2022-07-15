#pragma once
#include <Windows.h>
#include "Hooks.hpp"

namespace Gamemode {
	enum class Gamemodes {
		SOLO,
		DUOS,
		SQUADS,
		ENDGAME,
		SIPHON,
		THANOS,
		HIDEANDSEEK
	};

	Gamemodes CurrentGM = Gamemodes::SOLO;
}