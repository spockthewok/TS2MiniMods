#include "cinematic.h"

namespace
{
    const DWORD OncePerFrameUpdate_Exit = 0x5B76CF;
    const DWORD ComputeCameraToClipSpaceTransform_Exit = 0xF947A7;
    const float clipFarMult = 10.0;
    bool isCinematicActive = false;
}

namespace Cinematics
{
    // Steals the return value of the call to IsCinematicSceneActive in cTSWinSceneGraph::OncePerFrameUpdate()
    // We need this so we don't increase the far clip for ALL cameras, which would break things like thumbnails
    void __declspec(naked) GetCinematicActive()
    {
        __asm {
            call [eax+0xE0]
            mov [isCinematicActive],al
            jmp OncePerFrameUpdate_Exit
        }
    }

    void __declspec(naked) IncreaseCameraFarClip()
    {
        __asm {
            cmp [isCinematicActive],0x0
            je LAB_Exit
            fmul [clipFarMult]
        LAB_Exit:
            fstp [ebp+0xA0]
            jmp ComputeCameraToClipSpaceTransform_Exit
        }
    }
}