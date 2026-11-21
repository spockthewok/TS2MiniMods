#include "Patches/cinedrawdistance.h"
#include "headers.h"
#include "TS2/cTSSGSystem.h"

namespace
{
    constexpr DWORD ComputeCameraToClipSpaceTransform_Exit = 0xF947A7;
}

namespace MiniMods
{
    static float CalculateClipDepthMult(float clipDepth)
    {
        nTSSG::cTSSGSystem *system = *reinterpret_cast<nTSSG::cTSSGSystem **>(0x1478F10);

        // Thumbnail clipDepth < -1, this should better protect them from being affected
        if (system->IsCinematicSceneActive() && clipDepth >= -1)
            return clipDepth * 4.0f;

        return clipDepth;
    }

    // cViewerRefNodeImpl::ComputeCameraToClipSpaceTransform
    void __declspec(naked) IncreaseCineDrawDistance()
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