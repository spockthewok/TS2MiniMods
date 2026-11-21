#include "Patches/hiddencheats.h"
#include "hooking.h"
#include "TS2/base.h"

namespace
{
    constexpr DWORD TSAddOverlayCheats_Exit = 0xFE5B7E;
    constexpr DWORD AddEffectCheats_Exit_1 = 0xFFACF0;
    constexpr DWORD AddEffectCheats_Exit_2 = 0xFFAD1D;
}

// Based on TS2-HiddenCheats by LazyDuchess
// https://github.com/LazyDuchess/TS2-HiddenCheats
namespace MiniMods
{
    // (anonymous_namespace)::AddEffectCheats
    static void __declspec(naked) RegisterEffectCheat()
    {
        __asm {
            call cTSEffectCheat
            push eax
            call TSRegisterCheat
            pop eax
            jmp AddEffectCheats_Exit_1
        }
    }

    // (anonymous_namespace)::AddEffectCheats
    static void __declspec(naked) RegisterEffectsManagerCheat()
    {
        __asm {
            call cTSEffectsManagerCheat
            push eax
            call TSRegisterCheat
            pop eax
            jmp AddEffectCheats_Exit_2
        }
    }

    // TSAddOverlayCheats
    static void __declspec(naked) RegisterOverlayCheat()
    {
        __asm {
            call cOverlayCheat
            push eax
            call TSRegisterCheat
            pop eax
            jmp TSAddOverlayCheats_Exit
        }
    }

    void RestoreEffectCheats()
    {
        Hooking::MakeJMP((0xBFACEB + Module::base), (DWORD)RegisterEffectCheat, 5);
        Hooking::MakeJMP((0xBFAD18 + Module::base), (DWORD)RegisterEffectsManagerCheat, 5);
        Hooking::MakeJMP((0xBE5B79 + Module::base), (DWORD)RegisterOverlayCheat, 5);
    }

    // Hooks TSRegisterTestingCheat and forwards the call to TSRegisterCheat instead
    // Registers cheats exclusive to debug mode as regular cheats
    void AllowTestingCheats(void *cICommand)
    {
        TSRegisterCheat(cICommand);
    }
}