#include "cinematic.h"

namespace
{
    const DWORD OncePerFrameUpdate_Exit = 0x5B76CF;
    const DWORD ComputeCameraToClipSpaceTransform_Exit = 0xF947A7;

    bool cinematicActive = false;
}

namespace Cinematics
{
    // cTSWinSceneGraph::OncePerFrameUpdate
    // Stashes return value of the call to cTSSGSystem::IsCinematicSceneActive
    // We need this so we don't increase the clip depth for ALL cameras
    void __declspec(naked) GetCinematicActive()
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
            return clipDepth * 4;

        return clipDepth;
    }

    // cViewerRefNodeImpl::ComputeCameraToClipSpaceTransform
    void __declspec(naked) IncreaseCameraClipDepth()
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
}