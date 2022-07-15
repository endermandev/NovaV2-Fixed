#include "framework.h"

static void Main()
{
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    Util::Init();
    Hooks::KSM = decltype(Hooks::KSM)(Hooks::KSM->StaticClass());
    Hooks::UGS = decltype(Hooks::UGS)(Hooks::UGS->StaticClass());

    UE_LOG(LogNova, "Initialzing Nova...");

    if (MH_Initialize() != MH_OK)
        return;
    else
        UE_LOG(LogNova, "Failed to Initialize Nova...");

    auto BaseAddr = (uintptr_t)GetModuleHandle(0);
    GEngine = *(UFortEngine**)(BaseAddr + 0x4FC15D8);
    GWorld = &GEngine->GameViewport->World;
    FMemory_Free = decltype(FMemory_Free)(BaseAddr + 0x133D140);
    FMemory_Malloc = decltype(FMemory_Malloc)(BaseAddr + 0x13480A0);
    FMemory_Realloc = decltype(FMemory_Realloc)(BaseAddr + 0x134A390);

    UE_LOG(Log, "BaseAddr: {}", BaseAddr);
    UE_LOG(Log, "GEngine: {}", GEngine->GetFullName());
    UE_LOG(Log, "World: {}", GetWorld()->GetFullName());

    *reinterpret_cast<char*>(BaseAddr + 0xAEC475 + 0) = 0xE9;
    *reinterpret_cast<char*>(BaseAddr + 0xAEC475 + 1) = 0x39;
    *reinterpret_cast<char*>(BaseAddr + 0xAEC475 + 2) = 0x02;
    *reinterpret_cast<char*>(BaseAddr + 0xAEC475 + 3) = 0x00;
    *reinterpret_cast<char*>(BaseAddr + 0xAEC475 + 4) = 0x00;

    GEngine->GameInstance->LocalPlayers[0]->PlayerController->SwitchLevel(L"Athena_Terrain?game=athena");

    Hooks::Init();
    Abilities::Init();
}

int __stdcall DllMain(void*, int dwReason)
{
    if (dwReason == 1)
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Main, 0, 0, 0);

    return 1;
}

