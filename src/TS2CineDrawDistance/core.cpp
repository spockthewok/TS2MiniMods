#include "core.h"

namespace Core
{
    void InjectPatches()
    {
        Hooking::MakeJMP((BYTE *)0x5B76C9, (DWORD)Cinematics::GetCinematicActive, 6);
        Hooking::MakeJMP((BYTE *)0xF947A1, (DWORD)Cinematics::IncreaseCameraClipDepth, 6);
    }
}