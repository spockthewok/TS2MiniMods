#include "hooking.h"

DWORD WINAPI MainThread(LPVOID param)
{
    // cTSWinProcGameLoad::onTick()
    Hooking::Nop((BYTE *)0x5AFF30, 5); // ealogo_audio.movie
    Hooking::Nop((BYTE *)0x5B0172, 5); // intro_eng_audio.movie
    FreeLibraryAndExitThread((HMODULE)param, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, MainThread, hModule, 0, 0);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}