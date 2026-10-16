#include "Patches/cinedrawdistance.h"
#include "hooking.h"
#include "core.h"

namespace
{
    const DWORD OncePerFrameUpdate_Exit = 0x5B76CF;
    const DWORD ComputeCameraToClipSpaceTransform_Exit = 0xF947A7;

    bool cinematicActive = false;
}

namespace MiniMods
{
    // cTSWinSceneGraph::OncePerFrameUpdate
    // Stashes return value of the call to cTSSGSystem::IsCinematicSceneActive
    // We need this so we don't increase the clip depth for ALL cameras
    static void __declspec(naked) GetCinematicActive()
    {
        __asm {
            call [eax+0xE0]
            mov [cinematicActive],al
            jmp OncePerFrameUpdate_Exit
        }
    }

    static float CalculateClipDepthMult(float clipDepth)
    {
        // Thumbnail clipDepth < -1, this should better protect them from being affected
        if (cinematicActive && clipDepth >= -1)
            return clipDepth * 4.0;

        return clipDepth;
    }

    // cViewerRefNodeImpl::ComputeCameraToClipSpaceTransform
    static void __declspec(naked) IncreaseCameraClipDepth()
    {
        __asm {
            fstp [ebp+0xA0]
            push [ebp+0xA0]
            call CalculateClipDepthMult
            add esp,0x4
            fstp [ebp+0xA0]
            jmp ComputeCameraToClipSpaceTransform_Exit
        }
    }

    void IncreaseCineDrawDistance()
    {
        Hooking::MakeJMP((BYTE *)(0x1B76C9 + Core::modBase), (DWORD)GetCinematicActive, 6);
        Hooking::MakeJMP((BYTE *)(0xB947A1 + Core::modBase), (DWORD)IncreaseCameraClipDepth, 6);
    }
}