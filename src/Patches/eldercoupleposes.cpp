#include "Patches/eldercoupleposes.h"
#include "hooking.h"
#include "TS2/base.h"

namespace
{
    const BYTE maxAge = 0x33;
}

namespace MiniMods
{
    // cTSUIThumbnailFactoryFamily::FindCouples
    // if (32 < sVar2) -> if (33 < sVar2)
    void AllowElderCouplePoses()
    {
        Hooking::WriteToMemory((0x3AA7E + Module::base), &maxAge, sizeof(BYTE));
    }
}