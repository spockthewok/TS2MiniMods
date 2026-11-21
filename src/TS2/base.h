#pragma once
#include "headers.h"

namespace Module
{
    extern DWORD base;
}

// Actual param type is cICommand*
using TSRegisterCheatFn = void(__cdecl *)(void *);
extern TSRegisterCheatFn TSRegisterCheat;

// Params for these are (this*, cTSEffectsManager*)
using cOverlayCheatFn = void(__thiscall *)(void *);
extern cOverlayCheatFn cOverlayCheat;

using cTSEffectsManagerCheatFn = cOverlayCheatFn;
extern cTSEffectsManagerCheatFn cTSEffectsManagerCheat;

using cTSEffectCheatFn = cOverlayCheatFn;
extern cTSEffectCheatFn cTSEffectCheat;