#include "hooking.h"

DWORD WINAPI MainThread(LPVOID param)
{
    // cLotImposterManager::CreateDelauneyTerrainGeometry
    // FCOMP [DAT_01236770] -> FCOMP [DAT_011D79B4]
    // Decreases slope threshold required to add terrain vertex to imposter mesh from 4.1 to 0.25
    char slopeThreshold[3] = {0xB4, 0x79, 0x1D};
    Hooking::WriteToMemory((DWORD)0xA003DC, slopeThreshold, sizeof(slopeThreshold));
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