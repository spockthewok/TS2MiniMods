#include "TS2/base.h"

namespace Module
{
    DWORD base = 0x400000; // Default module base address
}

TSRegisterCheatFn TSRegisterCheat = reinterpret_cast<TSRegisterCheatFn>(0x63EA55);
cOverlayCheatFn cOverlayCheat = reinterpret_cast<cOverlayCheatFn>(0xFE59E0);
cTSEffectsManagerCheatFn cTSEffectsManagerCheat = reinterpret_cast<cTSEffectsManagerCheatFn>(0xFFA870);
cTSEffectCheatFn cTSEffectCheat = reinterpret_cast<cTSEffectCheatFn>(0xFFAA10);