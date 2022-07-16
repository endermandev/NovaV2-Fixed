#pragma once
#include <Windows.h>
#include "Hooks.hpp"

namespace Gamemode {
	enum class Gamemodes {
		SOLO, // Basic Solos
		DUOS, // Basic Duos
		SQUADS, // Basic Squads
		ENDGAME, // EndGame (WIP)
		SIPHON, // Siphon
		THANOS, // Thanos (WIP)
		HIDEANDSEEK, // Hide and Seek
		PLAYGROUND
	};

	Gamemodes CurrentGM = Gamemodes::SOLO;
}