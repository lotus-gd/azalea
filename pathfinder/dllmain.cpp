#include "pch.h"

#include "hooks.h"
#include "pathfinder.h"

DWORD WINAPI MainThread(void* hModule)
{
    AllocConsole();
    SetConsoleTitleA("Azalea Console");

    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONIN$", "r", stdin);
    std::ios::sync_with_stdio();

    printf("Welcome to Azalea Pathfinder for level difficulty calculation, developed by Midget.\n");

    /*Replay replay(26);
    replay.Set(2, true);
    replay.Set(8, true);
    replay.Set(6, true);
    replay.Set(6, false);
    printf("Replay: %s\n", replay.ToString().c_str());
    printf("Replay at 2: %s\n", replay[2] ? "1" : "0");
    printf("Replay at 7: %s\n", replay[7] ? "1" : "0");*/

    /*ReplayHandler replayHandler(3);
    replayHandler.Fail(2);
    replayHandler.Success();
    replayHandler.Fail(3);
    replayHandler.Fail(1);
    if (replayHandler.IsDone()) printf("Done\n");
    printf("Difficulty rating: %f%%\n", replayHandler.GetDifficulty());*/

    if (Hooks::Initialise())
        printf("Initialised successfully\n");
    else
        printf("Failed to initalise.\nPress enter to exit...\n");

    while (!Pathfinder::GetInstance()->IsDone()) Sleep(100);
    Sleep(5000);

    MH_Uninitialize();

    fclose(stdin);
    fclose(stdout);
    FreeConsole();

    FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(hModule), 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reasonForCall, LPVOID lpReserved)
{
    switch (reasonForCall)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0x1000, MainThread, hModule, 0, 0);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

